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

// fridge will be working or resting for at least this time
//#define FRIDGE_INTERVAL (3 * 60 * 1000)
#define FRIDGE_INTERVAL 180000

#define REPORT_INTERVAL (1 * 60 * 1000)

#define TARGET_TEMPERATURE 21.0
//#define TARGET_TEMPERATURE 14.0

// Ledkey
const int strobe = 2;
const int clock = 4;
const int data = 3;
const byte displayintensity = 3;

const int cooler = 7;
const int heater = 8;
const int fan = 9;

// fan 0-255
unsigned int fanpower = 85;

const int beersensorpin = 5;
const int chambersensorpin = 6;
/*
//RTC
// const int  cs=8; //chip select

// // Thermopins
// #define temp1 0
// #define temp2 1
// // DHT environment sensor
// #define DHTPIN 7
// #define DHTTYPE DHT11
*/
