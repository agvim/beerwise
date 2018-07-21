#ifndef LEDKEY_H
#define LEDKEY_H

#include <TM1638.h>
#include <Arduino.h>

class LedKey {
    public:
        LedKey(int data, int clock, int strobe);
        init(byte displayintensity);
        welcome();
        uint8_t getButtons();
        setLEDs(uint8_t leds);
        setDisplay(float number);
        setDisplay(float number1, float number2);
    private:
        TM1638 tm1638;
        uint8_t buttons;
};

#endif
