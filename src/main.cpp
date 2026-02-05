#include <Arduino.h>
#include <Wire.h>
#include <XPowersAXP2101.tpp>

XPowersAXP2101 pmu;

void setup()
{
  Serial.begin(115200);
  Wire.begin(21, 22);

  if (!pmu.init(Wire))
  {
    Serial.println("AXP2101 not detected");
    while (1)
      ;
  }

  Serial.println("PMU OK");
}

void loop() {}
