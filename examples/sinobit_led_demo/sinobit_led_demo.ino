#include <sinobit.h>


Sinobit matrix = Sinobit();

void setup() {
  matrix.begin();
  delay(100);
  matrix.fillScreen();
  delay(500);
  matrix.clearScreen();
  matrix.setTextWrap(false);
}

void loop() {

  matrix.clearScreen();
  // draw a pixel!
  matrix.drawPixel(0, 0, 1);
  matrix.writeScreen();

  delay(500);
  // clear a pixel!
  matrix.drawPixel(0, 0, 0);
  matrix.writeScreen();

  // draw a big rect on the screen
  matrix.fillRect(matrix.width() / 4, matrix.height() / 4,
                  matrix.width() / 2, matrix.height() / 2, 1);
  matrix.writeScreen();
  delay(500);

  // draw an outline
  matrix.drawRect(0, 0, matrix.width(), matrix.height(), 1);
  matrix.writeScreen();
  delay(500);

  // draw an 'X' in red
  matrix.clearScreen();
  matrix.drawLine(0, 0, matrix.width() - 1, matrix.height() - 1, 1);
  matrix.drawLine(matrix.width() - 1, 0, 0, matrix.height() - 1, 1);
  matrix.writeScreen();
  delay(500);

  // fill a circle
  matrix.clearScreen();
  matrix.fillCircle(matrix.width() / 2 - 1, matrix.height() / 2 - 1, 5, 1);
  matrix.writeScreen();
  delay(500);

  // draw an inverted circle
  matrix.drawCircle(matrix.width() / 2 - 1, matrix.height() / 2 - 1, 4, 0);
  matrix.writeScreen();
  delay(500);

  matrix.clearScreen();
  // draw some text!
  matrix.setTextSize(1);    // size 1 == 8 pixels high
  matrix.setTextColor(1);   // 'lit' LEDs
  matrix.setTextWrap(true);

  matrix.setCursor(0, 0);   // start at top left, with one pixel of spacing
  matrix.print("Hi");
  matrix.writeScreen();

  delay(2000);
  /*
    for (int16_t y = 0; y < matrix.height(); y++ ) {
      for (int16_t x = 0; x < matrix.width(); x++) {
        matrix.setPixel(x, y);
        matrix.writeScreen();
        delay(100);
        matrix.clrPixel(x, y);
        matrix.writeScreen();
      }
    }
  */
}

