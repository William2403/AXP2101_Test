#pragma once

#include <Arduino.h>
#include <functional>
#include <map>
#include <NimBLEDevice.h>

using BleCmdHandler = std::function<void(const String &, String &)>;

class BleConsole
{
public:
    bool begin(const char *deviceName);
    void registerCommand(const String &cmd, BleCmdHandler handler);
    void println(const String &msg);

private:
    void handleRx(const String &cmd);
    std::map<String, BleCmdHandler> handlers;
    NimBLECharacteristic *txChar = nullptr;
    static BleConsole *instance;
    class RxCallbacks : public NimBLECharacteristicCallbacks
    {
        void onWrite(NimBLECharacteristic *c);
    };
};
