#include <Arduino.h>
#include <Wire.h>

#include "Axp2101.h"
#include "BleConsole.h"

AXP2101 axp2101;
BLEConsole ble("ESP32-BLE-CONSOLE");

void handleCommand(String cmd)
{
  if (cmd == "status")
  {
    ble.send("STATUS: OK");
  }
  else if (cmd == "ping")
  {
    ble.send("pong");
  }
  else
  {
    ble.send("Unknown command");
  }
}

void setup()
{
  Serial.begin(115200);
  Wire.begin(21, 22);

  // AXP2101 Init
  if (!axp2101.begin())
  {
    Serial.println("ERROR: AXP2101 not detected");
    while (1)
      ;
  }

  ble.begin();
  ble.onCommand(handleCommand);

  // axp2101.printStatus(Serial);
}

void loop() {}
