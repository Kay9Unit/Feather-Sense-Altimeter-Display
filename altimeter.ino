/**
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>

2024 MATTHEW WALLACE
Adafruit Feather Sense Pressure Sensor (BMP280) "Altimeter"
*/

#include <Adafruit_BMP280.h>
#include <Adafruit_SH110X.h>
#include <Wire.h>

#define NOMINAL_PRESSURE 1019.2

#define BUTTON_A  9
#define BUTTON_B  6
#define BUTTON_C  5

Adafruit_BMP280 sensor;
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

void setup(void)
{
  Serial.begin(115200);

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  sensor.begin();

  display.begin(0x3C, true);
  display.clearDisplay();
  display.setRotation(1);
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.display();
}

float millibars = NOMINAL_PRESSURE;


void loop(void)
{
  // direct live adjustments to default mb value
  // using the OLED buttons
  if (!digitalRead(BUTTON_A)) millibars += 0.1;
  if (!digitalRead(BUTTON_B)) millibars = NOMINAL_PRESSURE;
  if (!digitalRead(BUTTON_C)) millibars -= 0.1;

  display.clearDisplay();
  display.setCursor(0, 0);

  display.print("Altitude: ");
  display.print(sensor.readAltitude(millibars));
  display.print("\nMillibars: ");
  display.print(millibars);

  display.display();
  delay(10);
  yield();
}