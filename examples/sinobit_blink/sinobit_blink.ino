// Blink the top-left LED in the matrix.

// Copyright (c) Dave Astels. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <sinobit.h>

Sinobit matrix = Sinobit();

void setup() {
  Serial.begin(9600);
  Serial.println("microbit is ready!");

  matrix.begin();
  delay(100);
  matrix.clearScreen();
}

void loop() {
  Serial.println("blink!");

  matrix.drawPixel(0, 0, 1);
  matrix.writeScreen();
  delay(500);
  // clear a pixel!
  matrix.drawPixel(0, 0, 0);
  matrix.writeScreen();
  delay(500);
}
