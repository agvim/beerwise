#ifndef DS18x20_H
#define DS18x20_H

#include <OneWire.h>
#include <Arduino.h>

class DS18x20 {
    public:
        DS18x20(uint8_t pin);
        float async_measure();
        int init();
    private:
        OneWire ow;
        byte addr[8]; // device address
        byte type_s; // device type
        unsigned long lasttime;
        float lastmeasurement = 0;

        start_conversion();
};

#endif
