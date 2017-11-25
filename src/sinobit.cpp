#include "sinobit.h"

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

Sinobit::Sinobit() : Adafruit_GFX(12, 12), leds(15, 13, 16) {}


boolean Sinobit::translate(int16_t x, int16_t y, int16_t *x_out, int16_t *y_out)
{
  if (y < 0 || y > 11 || x < 0 || x > 11) {
    return false;
  } else if ((y < 8 && x < 8) ||  (y > 7 && x > 7)) {
    *y_out = y;
    *x_out = x;
  } else if (y > 7 && x < 8) {
    *y_out = y - 8;
    *x_out = x + 8;
  } else if (y < 8 && x > 7) {
    *y_out = y + 8;
    *x_out = x - 8;
  }
  return true;
}

void Sinobit::setPixel(uint8_t x, uint8_t y) {
  drawPixel(x, y, 1);
}

void Sinobit::clrPixel(uint8_t x, uint8_t y) {
  drawPixel(x, y, 0);
}

void Sinobit::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) return;

  switch(rotation) { // Rotate pixel into device-specific coordinates
  case 1:
    _swap_int16_t(x, y);
    x = WIDTH  - 1 - x;
    break;
  case 2:
    x = WIDTH  - 1 - x;
    y = HEIGHT - 1 - y;
    break;
  case 3:
    _swap_int16_t(x, y);
    y = HEIGHT - 1 - y;
    break;
  }

  int16_t real_row, real_col;
  if (!translate(x, y, &real_col, &real_row)) return;

  uint16_t i;

  if (real_row < 8)       i =       7;
  else if (real_row < 16) i = 128 + 7;
  else                    i = 256 + 7;
  i -= (real_row & 7);

  if (real_col < 8) real_col *= 2;
  else              real_col  = (real_col-8) * 2 + 1;
  i += real_col * 8;

  if(color) leds.setPixel(i);
  else      leds.clrPixel(i);
}

boolean Sinobit::begin(uint8_t type) {
  leds.begin(type);
  return true;
}

void Sinobit::clearScreen() {
  leds.clearScreen();
}

void Sinobit::fillScreen() {
  leds.fillScreen();
}

void Sinobit::setBrightness(uint8_t b) {
  leds.setBrightness(b);
}

void Sinobit::blink(boolean b) {
  leds.blink(b);
}

void Sinobit::writeScreen() {
  leds.writeScreen();
}
