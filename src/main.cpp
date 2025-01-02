// libraries

#include <Arduino.h>
#include <Adafruit_LiquidCrystal.h>
#include <Keypad.h>
#include "arithmetic.h"
#include "conversion.h"

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
byte colPins_1[COLS_1] = {5, 6, 7, 8};        // keypad_1 Cols Pin

Keypad customKeypad_1 = Keypad(makeKeymap(keyMap_1), rowPins_1, colPins_1, ROWS_1, COLS_1); // keypad_1 object

// keypad_2

const byte ROWS_2 = 1; // number of Rows in keypad_2
const byte COLS_2 = 4; // number of Cols in keypad_2

char keyMap_2[ROWS_2][COLS_2] = { // values in keypad_2
    {'B', 'O', 'D', 'H'}};

byte rowPins_2[ROWS_2] = {2};              // keypad_2 Rows Pin
byte colPins_2[COLS_2] = {A0, A1, A2, A3}; // keypad_2 Cols Pin

Keypad customKeypad_2 = Keypad(makeKeymap(keyMap_2), rowPins_2, colPins_2, ROWS_2, COLS_2); // keypad_2 object

// LCD

Adafruit_LiquidCrystal lcd_1(0); // LCD object

// keypad_2 value storage

char base[1] = {}; // base currently in use for number system operation

// keypad_1 key processing

String keyPadValue;    // value in the keypad (accumulative)
char lastOperator = 0; // store the last operator (+, -, *, /)
float operand1 = 0, operand2 = 0;

float calculateResult(float op1, float op2, char oper)
{
  switch (oper)
  {
  case '+':
    return add(op1, op2);
  case '-':
    return subtract(op1, op2);
  case '*':
    return multiply(op1, op2);
  case '/':
    return divide(op1, op2);
  case '^':
    return exponencial(op1, op2);
  default:
    return 0;
  }
}

void processKey(char key)
{
  if (isdigit(key) || key == '.')
  { // if the value is a number
    if (key == '.' && keyPadValue.length() == 0)
    {
      keyPadValue = "0."; // if empty, append "0."
    }

    keyPadValue += key; // add key to string keyPadValue

    lcd_1.clear();            // clear LCD
    lcd_1.setCursor(0, 1);    // set cursor led to 0 col and 1 row
    lcd_1.print(keyPadValue); // print string in LCD

    delay(100); // wait 100ms
  }
  else
  { // if the value is not a number
    switch (key)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^': // if it's an operation
      if (keyPadValue.length() > 0)
      {                                                       // if expression is entered, update operand1 and operator
        operand1 = keyPadValue.toFloat();                     // value in the LCD is stored in first operand
        lastOperator = key;                                   // set the operator
        keyPadValue = "";                                     // clear for next operand
        lcd_1.setCursor(0, 1);                                // set cursor led to 0 col and 1 row
        lcd_1.print(String(operand1) + String(lastOperator)); // print string in LCD

        delay(100); // wait 100ms
      }
      else if (lastOperator != 0)
      {                                                       // if there is allready an operator change the operator
        lastOperator = key;                                   // set the operator
        lcd_1.setCursor(0, 1);                                // set cursor led to 0 col and 1 row
        lcd_1.print(String(operand1) + String(lastOperator)); // print string in LCD
      }
      break;

    case '=': // evaluate when user presses "="
      if (lastOperator && keyPadValue.length() > 0)
      {
        operand2 = keyPadValue.toFloat();                                 // value in the LCD is stored in second operand
        float result = calculateResult(operand1, operand2, lastOperator); // calculate result
        keyPadValue = String(result);                                     // Store result for display
        lastOperator = 0;                                                 // Reset operator
        lcd_1.clear();                                                    // clear LCD
        lcd_1.print(keyPadValue);                                         // display result
      }
      break;

    case 'A':                 // clear all
      operand1 = 0;           // set operand to 0
      operand2 = 0;           // set operand to 0
      lastOperator = 0;       // set operator to 0
      keyPadValue = "";       // set value current on display stored to ""
      lcd_1.clear();          // clear LCD
      lcd_1.print("Cleared"); // display message in LCD
      break;

    case 'C':                         // soft clear
      keyPadValue = "";               // set value current on display stored to ""
      lcd_1.clear();                  // clear LCD
      lcd_1.print("Operand Cleared"); // display message in LCD
      break;
    }
  }
}

void setup()
{
  Serial.begin(9600);

  lcd_1.begin(16, 2);             // start LCD
  lcd_1.print("Calculator V1.0"); // print string in LCD

  delay(1000);                   // wait 1000ms
  lcd_1.clear();                 // clear LCD
  lcd_1.print("Press a key..."); // print string in LCD
}

void loop()
{
  char key_1 = customKeypad_1.getKey(); // get the key clicked in keypad_1
  char key_2 = customKeypad_2.getKey(); // get the key clicked in keypad_2

  if (key_1 or key_2)
  {
    if (key_1)
    {
      if (base[0] == '\0') // if base it's empty
      {
        processKey(key_1); // process the key pressed
      }
      else
      {
        // needs to check if the value is in that base range
        switch (base[0])
        {
        case 'B':                           // base is set to binary
          if (key_1 == '0' || key_1 == '1') // can only use "01"
          {
            processKey(key_1); // process the key pressed
          }
          break;

        case 'O':                             // base is set to octal
          if ((key_1 >= '0' && key_1 <= '7')) // can only use "01234567"
          {
            processKey(key_1); // process the key pressed
          }
          break;

        case 'D':                           // base is set to decimal
          if (key_1 >= '0' && key_1 <= '9') // can only use "0123456789"
          {
            processKey(key_1); // process the key pressed
          }
          break;

        case 'H':                                                               // base is set to hexadecimal
          if ((key_1 >= '0' && key_1 <= '9') || (key_1 >= 'A' && key_1 <= 'F')) // can only use "0123456789ABCDEF"
          {
            processKey(key_1); // process the key pressed
          }
          break;
        }
      }
    }
    else // using the keypad_2
    {
      if (base[0] == '\0') // if base it's empty
      {
        base[0] = key_2;       // add selected base to the base array
        keyPadValue = "";      // set keypad value to ""
        lcd_1.clear();         // clear LCD
        lcd_1.setCursor(0, 1); // set cursor led to 0 col and 1 row
      }
      else // if base it's not empty
      {
        int befConv;   // value in mid conversion
        int baseValue; // value of the base stored

        switch (key_2)
        {
        case 'B':
          baseValue = 2; // binary
          break;
        case 'O':
          baseValue = 8; // octal
          break;
        case 'D':
          baseValue = 10; // decimal
          break;
        case 'H':
          baseValue = 16; // hexadecimal
          break;
        }

        switch (base[0])
        {
        case 'B': // conversion from binary
          befConv = conversionToDecimal(keyPadValue.c_str(), 2);
          keyPadValue = conversionFromDecimal(befConv, baseValue);
          lcd_1.clear();            // clear LCD
          lcd_1.print(keyPadValue); // display result
          break;

        case 'O': // conversion from octal
          befConv = conversionToDecimal(keyPadValue.c_str(), 8);
          keyPadValue = conversionFromDecimal(befConv, baseValue);
          lcd_1.clear();            // clear LCD
          lcd_1.print(keyPadValue); // display result
          break;

        case 'D': // conversion from decimal
          keyPadValue = conversionFromDecimal(keyPadValue.toInt(), baseValue);
          lcd_1.clear();            // clear LCD
          lcd_1.print(keyPadValue); // display result
          break;

        case 'H': // conversion from hexadecimal
          befConv = conversionToDecimal(keyPadValue.c_str(), 16);
          keyPadValue = conversionFromDecimal(befConv, baseValue);
          lcd_1.clear();            // clear LCD
          lcd_1.print(keyPadValue); // display result
          break;
        }
      }
    }
  }
}
