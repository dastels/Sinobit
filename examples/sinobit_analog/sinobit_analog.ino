// Read the analog signal on Pad P0 and use the LED matrix to display a historgram of the 12 most recent readings.

// Copyright (c) Dave Astels. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <sinobit.h>

Sinobit matrix = Sinobit();

int analogPin = SINOBIT_PAD_P0;
int readings[12];

void setup()
{
  matrix.begin();
  delay(100);
  matrix.clearScreen();
  for (int i = 0; i < 12; i++) {
    readings[i] = 0;
  }
}

void loop()
{
  delay(1000);

  for (int i = 0; i < 11; i++) {
    readings[i] = readings[i + 1];
  }
  readings[11] = map(analogRead(analogPin), 0, 1023, 0, 12);

  for (int i = 0; i < 12; i++) {
    if (readings[i] == 0) {
      matrix.drawLine(i, 11, i, 0, 0);
    } else if (readings[i] == 11) {
      matrix.drawLine(i, 11, i, 0, 1);
    } else {
      matrix.drawLine(i, 11, i, 12 - readings[i], 1);
      matrix.drawLine(i, 11 - readings[i], i, 0, 0);
    }
  }

  matrix.writeScreen();
}
