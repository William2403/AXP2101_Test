#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <XPowersAXP2101.tpp>

class AXP2101
{
public:
  bool begin(TwoWire &wire = Wire);

  // Battery
  float getBatteryVoltage();
  //float getBatteryCurrent();
  bool isBatteryConnected();
  bool isCharging();
  //uint8_t getChargeState();

  // Source
  float getVbusVoltage();
  bool isVbusPresent();

  // Enable Outputs
  bool enableDCDC1(bool enable);
  bool enableDCDC2(bool enable);
  bool enableDCDC3(bool enable);
  bool enableALDO1(bool enable);
  bool enableALDO2(bool enable);
  bool enableALDO3(bool enable);
  bool enableALDO4(bool enable);

  // Outputs State
  bool isDCDC1Enabled();
  bool isDCDC2Enabled();
  bool isDCDC3Enabled();
  bool isALDO1Enabled();
  bool isALDO2Enabled();
  bool isALDO3Enabled();
  bool isALDO4Enabled();

  // Debug
  void printStatus(Stream &out = Serial);

private:
  XPowersAXP2101 pmu;
};