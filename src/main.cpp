#include "main.h"

void setup()
{
    pinMode(cooler, OUTPUT);
    pinMode(heater, OUTPUT);
    pinMode(fan, OUTPUT);

    // slow down the fan
    analogWrite(fan, fanpower);

    // set serial port
    // Serial.begin(SERIAL_BPS);
    // Serial.println(VERSION);

    // Serial.println(FRIDGE_INTERVAL);
    // Serial.println(REPORT_INTERVAL);
    // Serial.println(TARGET_TEMPERATURE);

    // init LEDKEY display
    ledKey.init(displayintensity);

    ledKey.welcome();

    currtime = millis();

    // init the temperature sensor.
    while(tempSensorBeer.init() != -1){};
    while(tempSensorChamber.init() != -1){};

    //digitalWrite(cooler, HIGH);
    //digitalWrite(heater, HIGH);
}

/*
 * the application at the other end of the serial should log time.
 * we log when we act on any temperature change and periodically
 */
/*
void report(float celsius_beer, float celsius_chamber, bool cooling){
    //beer: '27.81', chamber: '27.75', cooling: '1'
    if(Serial.availableForWrite() > 7) Serial.print("beer: '");
    if(Serial.availableForWrite() > 5) Serial.print(celsius_beer, 2);
    if(Serial.availableForWrite() > 13) Serial.print("', chamber: '");
    if(Serial.availableForWrite() > 5) Serial.print(celsius_chamber, 2);
    if(Serial.availableForWrite() > 13) Serial.print("', cooling: '");
    if(Serial.availableForWrite() > 5) Serial.println(cooling ? "1'": "0'");
}
*/

// main
void loop(){
    float celsius_chamber, celsius_beer;

    //not using buttons at the moment
    buttons = ledKey.getButtons();
    ledKey.setLEDs(buttons);

    /*
    if(buttons & 0b1000){
        digitalWrite(cooler, HIGH);
    }
    else{
        digitalWrite(cooler, LOW);
        if(buttons & 0b0100){
            digitalWrite(heater, HIGH);
        }
        else{
            digitalWrite(heater, LOW);
        }
    }
    */

    currtime = millis();

    if (tempSensorChamber.error || tempSensorBeer.error){
        digitalWrite(cooler, LOW);
        cooling = false;
        digitalWrite(heater, LOW);
        heating = false;
        ledKey.setDisplay("ERROR SE");
        //if(tempSensorChamber.error){
            tempSensorChamber.init();
        //}
        //if(tempSensorBeer.error){
            tempSensorBeer.init();
        //}
    }
    else{
        // GET STATUS
        celsius_beer = tempSensorBeer.async_measure();
        celsius_chamber = tempSensorChamber.async_measure();
        // PRINT TEMPERATURES
        ledKey.setDisplay(celsius_beer, celsius_chamber);

        // Simple version, only start and stoop cooler depending on beer + chamber temperature and respecting fridge compressor rest intervals
        // TODO XXX FIXME: playing with thresholds here, the logic is also not optimal
        if((celsius_beer > (TARGET_TEMPERATURE + 1.0)) ||
           ((celsius_beer > (TARGET_TEMPERATURE + 0.5)) && (celsius_chamber > (TARGET_TEMPERATURE - 0.5)))
           ){
            // should cool, check last time we started the fridge
            if(!cooling){
                if((unsigned long)(currtime - lastfreezerstopped) > (unsigned long)FRIDGE_INTERVAL){
                    digitalWrite(cooler, HIGH);
                    cooling = true;
                    //report(celsius_beer, celsius_chamber, cooling);
                    lastfreezerstarted = currtime;
                }
            }
        } else if((celsius_beer < (TARGET_TEMPERATURE - 1.0)) ||
                  ((celsius_beer < (TARGET_TEMPERATURE - 0.5)) && (celsius_chamber < (TARGET_TEMPERATURE + 0.5)))
                ){
            if(cooling){
                if((unsigned long)(currtime - lastfreezerstarted) > (unsigned long)FRIDGE_INTERVAL){
                    digitalWrite(cooler, LOW);
                    cooling = false;
                    //report(celsius_beer, celsius_chamber, cooling);
                    lastfreezerstopped = currtime;
                }
            }
        }

        /*
        if((unsigned long)(currtime - lastserialupdate) > (unsigned long)REPORT_INTERVAL){
            //report(celsius_beer, celsius_chamber, cooling);
            lastserialupdate = currtime;
        }
        */
    }
}
        /*
        fanpower += 85;
        if (fanpower > 255) fanpower = 0;
        analogWrite(fan, fanpower);
        */
