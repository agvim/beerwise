#include "LedKey.h"

LedKey::LedKey(int data, int clock, int strobe): tm1638(data, clock, strobe){}

LedKey::init(byte displayintensity){
    this->tm1638.setupDisplay(true, displayintensity);
}

LedKey::welcome(){
    // flash leds
    // off
    this->tm1638.setLEDs(0);
    delay(500);
    // red
    this->tm1638.setLEDs(0xFF);
    delay(500);
    // off
    this->tm1638.setLEDs(0);
    for (int i=0;i<8;i++) {
        this->tm1638.setLED(TM1638_COLOR_RED, i);
        delay(200);
        this->tm1638.setLED(0, i);
    }

    // print strings
    this->tm1638.setDisplayToString("HELLO  ");
    delay(1000);
    this->tm1638.clearDisplay();
    delay(500);
    this->tm1638.setDisplayToString("BEERWISE");
    delay(1000);
    this->tm1638.clearDisplay();
    delay(500);
}

uint8_t LedKey::getButtons(){
    return this->tm1638.getButtons();
}

LedKey::setLEDs(uint8_t leds){
    tm1638.setLEDs(leds);
}

/*
void display_temps(float t1, float t2){
    const byte dots=0b01000100;
    unsigned long it1 = t1 * 100;
    unsigned long it2 = t2 * 100;
    tm1638.setDisplayToDecNumber(it1 * 10000 + it2, dots);
}
*/

LedKey::setDisplay(float number){
    const byte dots=0b00000100;
    unsigned long inumber = number * 100;
    // last boolean false for no leading zeroes
    this->tm1638.setDisplayToDecNumber(inumber, dots, false);
}

LedKey::setDisplay(float number1, float number2){
    const byte dots=0b01000100;
    unsigned long n1 = number1 * 100.0;
    unsigned long n2 = number2 * 100.0;
    unsigned long inumber = n1 * 10000;
    inumber += n2;
    this->tm1638.setDisplayToDecNumber(inumber, dots, false);
}
