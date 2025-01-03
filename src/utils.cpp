#include "utils.h"

// implementation of updateLCD
void updateLCD(const String &message) {
  lcd_1.clear();
  lcd_1.setCursor(0, 1);
  lcd_1.print(message);
}
