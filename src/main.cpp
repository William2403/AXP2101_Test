#include <Arduino.h>
#include <Wire.h>

#include "Axp2101.h"
#include "BleConsole.h"

AXP2101 axp2101;
BleConsole ble;

void setup()
{
  Serial.begin(115200);
  Wire.begin(21, 22);

  // AXP2101 Init
  if (!axp2101.begin())
  {
    Serial.println("ERROR: AXP2101 no detectado");
    while (1)
      ;
  }

  // BLE Init
  ble.begin("AXP2101-Console");

  // ===== COMMANDS =====

  // Status
  ble.registerCommand("status", [&](const String &, String &out)
                      {
        out  = "Battery: " + String(axp2101.getBatteryVoltage(), 2) + " V\n";
        out += axp2101.isCharging() ? "Charging\n" : "Not charging\n";
        out += axp2101.isVbusPresent() ? "VBUS present\n" : "VBUS absent\n"; });

  // Battery
  ble.registerCommand("bat", [&](const String &, String &out)
                      { out = "Battery: " + String(axp2101.getBatteryVoltage(), 2) + " V\n"; });

  // DCDC1 (⚠)
  ble.registerCommand("dcdc1 on", [&](const String &, String &out)
                      {
        axp2101.enableDCDC1(true);
        out = "DCDC1 ON\n"; });

  ble.registerCommand("dcdc1 off", [&](const String &, String &out)
                      { out = "BLOCKED (unsafe)\n"; });

  Serial.println("System ready");

  axp2101.printStatus(Serial);
}

void loop() {}
