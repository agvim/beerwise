#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>

#include "Arduino.h"

#define VERSION      "\nBEERWISE TEMP CONTROL 0.0.1"
#define SERIAL_BPS   57600

// Ledkey
const int strobe = 2;
const int clock = 4;
const int data = 3;
const byte displayintensity = 3;

const int cooler = 6;
const int heater = 7;
const int sensorpin = 5;
/*
//RTC
// const int  cs=8; //chip select

// // Thermopins
// #define temp1 0
// #define temp2 1
// // DHT environment sensor
// #define DHTPIN 7
// #define DHTTYPE DHT11

// modes
#define MODE_DISPLAY 0x0
#define MODE_SET 0x1

// buttons
#define BUTTON_OK     0
#define BUTTON_CANCEL 1
#define BUTTON_PLUS   2
#define BUTTON_MINUS  3
*/
