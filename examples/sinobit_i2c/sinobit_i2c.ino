// I2C demo
// Requires and external SSD1306 based OLED screen and Si7021 temperature/humidity sensor.
// External temperature & humidity, as well as onboard accelerometer & magetometer are displayed on the OLED

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Si7021.h>
#include "MMA8653.h"
#include <SparkFun_MAG3110.h>

MMA8653 accel;
Adafruit_Si7021 sensor = Adafruit_Si7021();
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
MAG3110 mag = MAG3110();

void setup() {
  sensor.begin();
  accel.begin(false, 2);
  mag.initialize();
  mag.start();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();
}

int convert(int x) {
  if (x < 32768) {
    return x;
  } else {
    return -1 * (65536 - x);
  }
}
void loop() {
  double temperature = sensor.readTemperature();
  double humidity = sensor.readHumidity();
  accel.update();
  int x, y, z;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature);
  display.print(" RH: ");
  display.println(humidity);
  display.print((float)accel.getX() * 0.0156);
  display.print(" ");
  display.print((float)accel.getY() * 0.0156);
  display.print(" ");
  display.println((float)accel.getZ() * 0.0156);
  if (mag.dataReady()) {
    mag.readMag(&x, &y, &z);
    display.print(convert(x));
    display.print(" ");
    display.print(convert(y));
    display.print(" ");
    display.println(convert(z));
  }
  display.display();
}
