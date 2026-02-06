#include <Arduino.h>
#include <Wire.h>

#include "axp2101.h"

AXP2101 axp2101;

void setup()
{
  Serial.begin(115200);
  axp2101.begin(Wire);

  axp2101.printStatus(Serial);
}

void loop() {}
