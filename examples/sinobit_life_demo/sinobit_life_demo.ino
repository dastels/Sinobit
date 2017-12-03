// Play Conway's game of life on the LED matrix.
// Based on code by Phillip Burgess in https://learn.adafruit.com/mini-commodore-pet-with-charlieplexed-led-matrix/software

// Copyright (c) Dave Astels. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <sinobit.h>

Sinobit matrix = Sinobit();

#define WIDTH  (12)        // Matrix size in pixels
#define HEIGHT (12)
#define BITMAP_SIZE (24)   // memory size of bitmap storage

uint8_t bitmap[BITMAP_SIZE], // Buffer we build for the next generation
        oldBitmap[BITMAP_SIZE], // Buffer for the currently displayed generation
        frame = 0;

// Set bit at (x,y) in the bitmap buffer (no clear function, wasn't needed)
void bitmapSetPixel(uint8_t *b, int8_t x, int8_t y) {
  b[y * 2 + x / 8] |= (0x80 >> (x & 7));
}

// Read bit at (x,y) in bitmap buffer, returns nonzero (not always 1) if set
uint8_t bitmapGetPixel(uint8_t *b, int8_t x, int8_t y) {
  return b[y * 2 + x / 8] & (0x80 >> (x & 7));
}


boolean allDead() {
  uint8_t sum = 0;
  for (uint8_t i = 0; i < sizeof(bitmap); i++) {
    sum |= bitmap[i];
  }
  return sum == 0;
}


boolean unchanged() {
  for (uint8_t i = 0; i < sizeof(bitmap); i++) {
    if (bitmap[i] != oldBitmap[i]) {
      return false;
    }
  }
  return true;
}


// CONWAY'S GAME OF LIFE ---------------------------------------------------
// The rules: if cell at (x,y) is currently populated, it stays populated
// if it has 2 or 3 populated neighbors, else is cleared.  If cell at (x,y)
// is currently empty, populate it if 3 neighbors.

void lifeSetup() { // Fill bitmap with random data
  frame = 0;
  for (uint8_t i = 0; i < sizeof(bitmap); i++) {
    uint8_t r = random(256);
    bitmap[i] = ((i % 2) == 0) ? r : (r & 0xF0);
  }
}

boolean lifeLoop() {
  static const int8_t xo[] = { -1,  0,  1, -1, 1, -1, 0, 1 },
                      yo[] = { -1, -1, -1,  0, 0,  1, 1, 1 };
  int8_t              x, y;
  uint8_t             i, n;

  memcpy(oldBitmap, bitmap, sizeof(bitmap));  // save the current generation to use in makign the next one

  // Generate new bitmap (next frame) based on oldBitmap contents + rules
  memset(bitmap, 0, sizeof(bitmap));
  for (y = 0; y < HEIGHT; y++) {
    for (x = 0; x < WIDTH; x++) {
      for (i = n = 0; (i < sizeof(xo)) && (n < 4); i++) {
        n += (bitmapGetPixel(oldBitmap, (x + xo[i]) % WIDTH, (y + yo[i]) % HEIGHT) ? 1 : 0);
      }
      if ((n == 3) || ((n == 2) && bitmapGetPixel(oldBitmap, x, y))) {
        bitmapSetPixel(bitmap, x, y);
      }
    }
  }

  if (allDead()) {
    return 0;
  }

  // Every 16 frames, populate a random cell so animation doesn't stagnate
  // Also, if two successive generations are identical, mutate.
  if (unchanged() || !(frame & 0x0F)) {
    bitmapSetPixel(bitmap, random(WIDTH), random(HEIGHT));
  }

  return 1;
}


void updateDisplay() {
  for (int8_t y = 0; y < HEIGHT; y++) {
    for (int8_t x = 0; x < WIDTH; x++) {
      matrix.drawPixel(x, y, bitmapGetPixel(bitmap, x, y) ? 1 : 0);
    }
  }
  matrix.writeScreen();
}


void setup() {
  matrix.begin();
  delay(100);
  matrix.fillScreen();
  delay(500);
  matrix.clearScreen();
  matrix.setTextWrap(false);

  lifeSetup();
}


void loop() {
  if (!lifeLoop()) {
    lifeSetup();
  } else {
    frame++;
  }
  updateDisplay();
  delay(200);
}
