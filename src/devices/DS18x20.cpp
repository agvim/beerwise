#include "DS18x20.h"

DS18x20::DS18x20(uint8_t pin): ow(pin){}

DS18x20::start_conversion(){
    this->ow.reset();
    this->ow.select(this->addr);
    // start conversion, with parasite power on at the end
    this->ow.write(0x44, 1);
}

int DS18x20::init(){
    byte i;
    // TODO XXX FIXME ERROR TOLERANCE
    if ( !this->ow.search(addr)) {
        //Serial.println("No more addresses.");
        //Serial.println();
        this->ow.reset_search();
        //delay(250);
        return -1;
    }

    /*
    //Serial.print("ROM =");
    for( i = 0; i < 8; i++) {
        Serial.write(' ');
        Serial.print(addr[i], HEX);
    }
    */

    if (OneWire::crc8(this->addr, 7) != this->addr[7]) {
        //Serial.println("CRC is not valid!");
        return -1;
    }
    // Serial.println();

    // the first ROM byte indicates which chip
    switch (this->addr[0]) {
        case 0x10:
            // Serial.println("  Chip = DS18S20");  // or old DS1820
            this->type_s = 1;
            break;
        case 0x28:
            // Serial.println("  Chip = DS18B20");
            this->type_s = 0;
            break;
        case 0x22:
            // Serial.println("  Chip = DS1822");
            this->type_s = 0;
            break;
        default:
            // Serial.println("Device is not a DS18x20 family device.");
            return -1;
    }

    this->start_conversion();
    // delay(1000);     // maybe 750ms is enough, maybe not
    // keep track of how long ago we made a measurement
    this->lasttime = millis();
}

float DS18x20::async_measure(){

    byte i;
    byte present = 0;
    byte data[12];
    float celsius;

    long currtime = millis();

    // if timer overflow or less than 1000 millis passed, return last measurement
    if((currtime < lasttime) | ((currtime - this->lasttime) < 1000)){
        return this->lastmeasurement;
    }
    if((currtime - this->lasttime) >= 1000){
        // we might do a ow.depower() here, but the reset will take care of it.
        present = ow.reset();
        ow.select(addr);
        ow.write(0xBE);         // Read Scratchpad

        /*
        Serial.print("  Data = ");
        Serial.print(present, HEX);
        Serial.print(" ");
        */
        for(i = 0; i < 9; i++) {           // we need 9 bytes
            data[i] = ow.read();
            /*
            Serial.print(data[i], HEX);
            Serial.print(" ");
            */
        }
        /*
        Serial.print(" CRC=");
        Serial.print(OneWire::crc8(data, 8), HEX);
        Serial.println();
        */
        if (OneWire::crc8(data, 8) != data[8]) {
            Serial.println("CRC is not valid!");
            return 0;
        }

        // Convert the data to actual temperature
        // because the result is a 16 bit signed integer, it should
        // be stored to an "int16_t" type, which is always 16 bits
        // even when compiled on a 32 bit processor.
        int16_t raw = (data[1] << 8) | data[0];
        if (type_s) {
            raw = raw << 3; // 9 bit resolution default
            if (data[7] == 0x10) {
                // "count remain" gives full 12 bit resolution
                raw = (raw & 0xFFF0) + 12 - data[6];
            }
        } else {
            byte cfg = (data[4] & 0x60);
            /*
            Serial.print(cfg, HEX);
            Serial.println(" cfg"); //in our case it is 12 bit
            */
            // at lower res, the low bits are undefined, so let's zero them
            if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
            else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
            else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
            //// default is 12 bit resolution, 750 ms conversion time
        }
        // start conversion again
        this->start_conversion();
        // delay(1000);     // maybe 750ms is enough, maybe not
        this->lasttime = millis();

        // convert to celcius and return the value
        this->lastmeasurement = (float)raw / 16.0;
        return this->lastmeasurement;
    }
}
