#include "main.h"

void setup()
{
    // pins for leds
    pinMode(cooler, OUTPUT);
    pinMode(heater, OUTPUT);
    // fan is always on

    // set serial port
    Serial.begin(SERIAL_BPS);
    Serial.println(VERSION);

    // init the temperature sensor
    tempSensor1.init();

    // init LEDKEY display
    ledKey.init(displayintensity);

    ledKey.welcome();

    lasttime = millis();
}

// main
void loop(){
    float celsius;

    lasttime = millis();
    buttons = ledKey.getButtons();
    ledKey.setLEDs(buttons);

    celsius = tempSensor1.async_measure();
    ledKey.setDisplay(celsius);
    if(celsius < 30.){
        digitalWrite(cooler, LOW);
        digitalWrite(heater, HIGH);
    }
    else{
        digitalWrite(cooler, HIGH);
        digitalWrite(heater, LOW);
    }
}
