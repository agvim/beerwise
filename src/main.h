#include <Arduino.h>
#include "devices/DS18x20.h"
#include "devices/LedKey.h"
#include "configure.h"

volatile uint8_t buttons;

unsigned long currtime;

// freezer control
unsigned long lastfreezerstopped = 0, lastfreezerstarted = 0, lastserialupdate = 0;
bool cooling = false;
bool heating = false;

// ledkey display
LedKey ledKey(data, clock, strobe);

// temperature sensor
DS18x20 tempSensorBeer(beersensorpin);
DS18x20 tempSensorChamber(chambersensorpin);

void setup(void);
void loop(void);
