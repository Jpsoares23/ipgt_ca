#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <Adafruit_LiquidCrystal.h>

// declare the LCD object externally
extern Adafruit_LiquidCrystal lcd_1;

// function declaration
void updateLCD(const String &message);

#endif
