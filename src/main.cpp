// libraries
#include <Arduino.h>
#include <Adafruit_LiquidCrystal.h>
#include <Keypad.h>

// keypad_1

const byte ROWS_1 = 5; // number of Rows in keypad_1
const byte COLS_1 = 4; // number of Cols in keypad_1

char keyMap_1[ROWS_1][COLS_1] = { // values in Keypad_1
  {'C', 'A', '^', '%'},
  {'7', '8', '9', '/'}, 
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'.', '0', '=', '+'}
};


byte rowPins_1[ROWS_1] = {9, 10, 11, 12, 13}; // keypad_1 Rows Pin
byte colPins_1[COLS_1] = {5, 6, 7, 8}; // keypad_1 Cols Pin

Keypad customKeypad_1 = Keypad(makeKeymap(keyMap_1), rowPins_1, colPins_1, ROWS_1, COLS_1); // keypad_1 object

// keypad_2

const byte ROWS_2 = 1;
const byte COLS_2 = 4;

char keyMap_2[ROWS_2][COLS_2] = { // values in keypad_2
    {'B', 'O', 'D', 'H'}
};

byte rowPins_2[ROWS_2] = {2}; // keypad_2 Rows Pin
byte colPins_2[COLS_2] = {A0, A1, A2, A3}; // keypad_2 Cols Pin

Keypad customKeypad_2 = Keypad(makeKeymap(keyMap_2), rowPins_2, colPins_2, ROWS_2, COLS_2); // keypad_2 object

// LCD
Adafruit_LiquidCrystal lcd_1(0); // LCD object

void setup() {
  Serial.begin(9600);
    
  lcd_1.begin(16, 2); // start LCD
  lcd_1.print("Calculator V1.0"); // print string in LCD
  
  delay(1000); // wait 1000ms
  lcd_1.clear(); // clear LCD
  lcd_1.print("Press a key..."); // print string in LCD
}

void loop() {

}
