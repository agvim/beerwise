#include "main.h"

void setup()
{
    // pins for leds
    pinMode(cooler, OUTPUT);
    // fan is always on

    // set serial port
    Serial.begin(SERIAL_BPS);
    Serial.println(VERSION);

    // init the temperature sensor. TODO XXX FIXME: ASSUMING THEY WORK
    tempSensorBeer.init();
    tempSensorChamber.init();

    // init LEDKEY display
    ledKey.init(displayintensity);

    ledKey.welcome();

    currtime = millis();
}

/*
 * the application at the other end of the serial should log time.
 * we log when we act on any temperature change and periodically
 */
void report(float celsius_beer, float celsius_chamber, bool cooling){
    Serial.print("beer: '");
    Serial.print(celsius_beer, 2);
    Serial.print("', chamber: '");
    Serial.print(celsius_chamber, 2);
    Serial.print("', cooling:'");
    Serial.println(cooling ? "1'": "0'");
}

// main
void loop(){
    float celsius_chamber, celsius_beer;

    //not using buttons at the moment
    /*
    buttons = ledKey.getButtons();
    ledKey.setLEDs(buttons);
    */

    // GET STATUS AND PRINT IT
    celsius_beer = tempSensorBeer.async_measure();
    celsius_chamber = tempSensorChamber.async_measure();
    ledKey.setDisplay(celsius_beer, celsius_chamber);

    currtime = millis();

    // Simple version, only start and stoop cooler depending on beer + chamber temperature and respecting fridge compressor rest intervals
    // TODO XXX FIXME: playing with thresholds here, the logic is also not optimal
    if((celsius_beer > (TARGET_TEMPERATURE + 0.5)) ||
       ((celsius_beer > (TARGET_TEMPERATURE + 0.25)) && (celsius_chamber > (TARGET_TEMPERATURE - 0.25)))
       ){
        // should cool, check last time we started the fridge
        if(!cooling){
            if((currtime - lastfreezerstopped) > FRIDGE_INTERVAL){
                cooling = true;
                digitalWrite(cooler, HIGH);
                lastfreezerstarted = currtime;
            }
        }
    } else if((celsius_beer < (TARGET_TEMPERATURE - 0.5)) ||
              ((celsius_beer < (TARGET_TEMPERATURE - 0.25)) && (celsius_chamber < (TARGET_TEMPERATURE + 0.25)))
            ){
        if(cooling){
            if((currtime - lastfreezerstarted) > FRIDGE_INTERVAL){
                cooling = false;
                digitalWrite(cooler, LOW);
                lastfreezerstopped = currtime;
            }
        }
    }

    // report via serial
    if((currtime - lastserialupdate) > REPORT_INTERVAL){
        report(celsius_beer, celsius_chamber, cooling);
        lastserialupdate = currtime;
    }
}
