// libraries

#include <Arduino.h>
#include <Adafruit_LiquidCrystal.h>
#include <Keypad.h>
#include <arithmetic.cpp>

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

const byte ROWS_2 = 1; // number of Rows in keypad_2
const byte COLS_2 = 4; // number of Cols in keypad_2

char keyMap_2[ROWS_2][COLS_2] = { // values in keypad_2
    {'B', 'O', 'D', 'H'}
};

byte rowPins_2[ROWS_2] = {2}; // keypad_2 Rows Pin
byte colPins_2[COLS_2] = {A0, A1, A2, A3}; // keypad_2 Cols Pin

Keypad customKeypad_2 = Keypad(makeKeymap(keyMap_2), rowPins_2, colPins_2, ROWS_2, COLS_2); // keypad_2 object

// LCD

Adafruit_LiquidCrystal lcd_1(0); // LCD object

// keypad_1 and keypad_2 value storage

String keyPadValue; // value in the keypad (accumulative)
char base[1] = {}; // base currently in use for number system operation

// keypad_1 key processing 

void processKey(char key) {
  keyPadValue += key; // add key to string keyPadValue
  
  lcd_1.clear(); // clear LCD
  lcd_1.setCursor(0, 1); // set cursor led to 0 col and 1 row
  lcd_1.print(keyPadValue); // print string in LCD
  
  delay(100); // wait 100ms
}

void setup() {
  Serial.begin(9600);
    
  lcd_1.begin(16, 2); // start LCD
  lcd_1.print("Calculator V1.0"); // print string in LCD
  
  delay(1000); // wait 1000ms
  lcd_1.clear(); // clear LCD
  lcd_1.print("Press a key..."); // print string in LCD
}

void loop() {
  char key_1 = customKeypad_1.getKey(); // get the key clicked in keypad_1
  char key_2 = customKeypad_2.getKey(); // get the key clicked in keypad_2

  if (key_1 or key_2) {
    if (key_1) {
      if (sizeof(base) / sizeof(base[0]) > 0){ // if base it's empty
        processKey(key_1);
      } else {
        // needs to check if the value is in that base range
      }
    } else {
      if (sizeof(base) / sizeof(base[0]) > 0){ // if base it's empty 
        base[0]= key_2; // add selected base to the base array
        lcd_1.clear(); // clear LCD
        lcd_1.setCursor(0, 1); // set cursor led to 0 col and 1 row
      }
      else{
        // base already exists need to do the conversion
      }
      }
    }
  }
