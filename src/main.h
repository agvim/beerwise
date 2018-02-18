#include <Arduino.h>
#include "devices/DS18x20.h"
#include "devices/LedKey.h"
#include "configure.h"

volatile uint8_t buttons;

unsigned long lasttime;

// ledkey display
LedKey ledKey(data, clock, strobe);

// temperature sensor
DS18x20 tempSensor1(sensorpin);

void setup(void);
void loop(void);
