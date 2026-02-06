#include "AXP2101.h"

#include "AXP2101.h"

bool AXP2101::begin(TwoWire &wire)
{
  if (!pmu.init(wire))
  {
    Serial.println("AXP2101 not detected");
    return false;
  }
  enableBatteryCharge(true);
  enableVbusMeasure(true);
  return true;
}

// Battery
float AXP2101::getBatteryVoltage()
{
  return pmu.getBattVoltage();
}

// float AXP2101::getBatteryCurrent()
// {
//   return pmu.getBattDischargeCurrent();
// }

bool AXP2101::isBatteryConnected()
{
  return pmu.isBatteryConnect();
}

bool AXP2101::isCharging()
{
  return pmu.isCharging();
}

// uint8_t AXP2101::getChargeState()
// {
//   return pmu.getChargeState();
// }

// VBUS
float AXP2101::getVbusVoltage()
{
  return pmu.getVbusVoltage();
}

bool AXP2101::isVbusPresent()
{
  return pmu.isVbusIn();
}

// Charger / ADC helpers
bool AXP2101::enableBatteryCharge(bool enable)
{
  if (enable)
  {
    pmu.enableCellbatteryCharge();
    return true;
  }
  else
  {
    pmu.disableCellbatteryCharge();
    return true;
  }
}

bool AXP2101::enableVbusMeasure(bool enable)
{
  return enable ? pmu.enableVbusVoltageMeasure() : pmu.disableVbusVoltageMeasure();
}

// Enable Outputs
bool AXP2101::enableDCDC1(bool enable)
{
  return enable ? pmu.enableDC1() : pmu.disableDC1();
}

bool AXP2101::enableDCDC2(bool enable)
{
  return enable ? pmu.enableDC2() : pmu.disableDC2();
}

bool AXP2101::enableDCDC3(bool enable)
{
  return enable ? pmu.enableDC3() : pmu.disableDC3();
}

bool AXP2101::enableALDO1(bool enable)
{
  return enable ? pmu.enableALDO1() : pmu.disableALDO1();
}

bool AXP2101::enableALDO2(bool enable)
{
  return enable ? pmu.enableALDO2() : pmu.disableALDO2();
}

bool AXP2101::enableALDO3(bool enable)
{
  return enable ? pmu.enableALDO3() : pmu.disableALDO3();
}

bool AXP2101::enableALDO4(bool enable)
{
  return enable ? pmu.enableALDO4() : pmu.disableALDO4();
}

// Outputs State
bool AXP2101::isDCDC1Enabled() { return pmu.isEnableDC1(); }
bool AXP2101::isDCDC2Enabled() { return pmu.isEnableDC2(); }
bool AXP2101::isDCDC3Enabled() { return pmu.isEnableDC3(); }
bool AXP2101::isALDO1Enabled() { return pmu.isEnableALDO1(); }
bool AXP2101::isALDO2Enabled() { return pmu.isEnableALDO2(); }
bool AXP2101::isALDO3Enabled() { return pmu.isEnableALDO3(); }
bool AXP2101::isALDO4Enabled() { return pmu.isEnableALDO4(); }

// Debug
void AXP2101::printStatus(Stream &out)
{
  out.println("=== AXP2101 STATUS ===");
  out.printf("BATT: %.2f V | %s\n",
             getBatteryVoltage(),
             isCharging() ? "Charging" : "Not charging");

  out.printf("VBUS: %.2f V | %s\n",
             getVbusVoltage(),
             isVbusPresent() ? "Present" : "Absent");

  out.printf("DCDC1: %d  DCDC2: %d  DCDC3: %d\n",
             isDCDC1Enabled(),
             isDCDC2Enabled(),
             isDCDC3Enabled());

  out.printf("ALDO1: %d  ALDO2: %d  ALDO3: %d  ALDO4: %d\n",
             isALDO1Enabled(),
             isALDO2Enabled(),
             isALDO3Enabled(),
             isALDO4Enabled());
}