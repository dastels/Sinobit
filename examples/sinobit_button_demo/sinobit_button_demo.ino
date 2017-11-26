#include <sinobit.h>

Sinobit matrix = Sinobit();

void setup() {
  matrix.begin();
  delay(100);
  matrix.clearScreen();
  matrix.setTextWrap(false);

  pinMode(SINOBIT_BUTTON_A, INPUT);
  pinMode(SINOBIT_BUTTON_B, INPUT);
}

void loop() {
  if (!digitalRead(SINOBIT_BUTTON_A)) {
    matrix.drawLine(7, 1, 11, 5, 1);
    matrix.drawLine(7, 10, 11, 6, 1);
  } else {
    matrix.drawLine(7, 1, 11, 5, 0);
    matrix.drawLine(7, 10, 11, 6, 0);
  }

  if (!digitalRead(SINOBIT_BUTTON_B)) {
    matrix.drawLine(4, 1, 0, 5, 1);
    matrix.drawLine(4, 10, 0, 6, 1);
  } else {
    matrix.drawLine(4, 1, 0, 5, 0);
    matrix.drawLine(4, 10, 0, 6, 0);  
  }

  matrix.writeScreen();
}
