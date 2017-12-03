// Pulse each of the Pad connections, sequentially and repeatedly.

// Copyright (c) Dave Astels. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <sinobit.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(SINOBIT_PAD_P0, OUTPUT);
  pinMode(SINOBIT_PAD_P1, OUTPUT);
  pinMode(SINOBIT_PAD_P2, OUTPUT);
  pinMode(SINOBIT_PAD_P3, OUTPUT);
  pinMode(SINOBIT_PAD_P4, OUTPUT);
  pinMode(SINOBIT_PAD_P5, OUTPUT);
}

void pulse(int io_pin, int count)
{
  for (int i = 0; i < count; i++) {
    digitalWrite(io_pin, HIGH);
    delay(100);
    digitalWrite(io_pin, LOW);
    delay(100);
  }
}

void loop() {
  pulse(SINOBIT_PAD_P0, 1);
  pulse(SINOBIT_PAD_P1, 1);
  pulse(SINOBIT_PAD_P2, 1);
  pulse(SINOBIT_PAD_P3, 1);
  pulse(SINOBIT_PAD_P4, 1);
  pulse(SINOBIT_PAD_P5, 1);
}
