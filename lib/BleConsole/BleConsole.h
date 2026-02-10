#pragma once

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

class BLEConsole
{
public:
    BLEConsole(const char *deviceName);
    void begin();

    // Para enviar mensajes al celular
    void send(const String &msg);

    // Callback de usuario (cuando llega un comando)
    void onCommand(void (*callback)(String cmd));

private:
    const char *_deviceName;
    BLECharacteristic *_txChar;
    bool _deviceConnected = false;

    void (*_userCallback)(String) = nullptr;

    // Callbacks internos
    class ServerCallbacks : public BLEServerCallbacks
    {
    public:
        ServerCallbacks(BLEConsole *parent);
        void onConnect(BLEServer *pServer) override;
        void onDisconnect(BLEServer *pServer) override;

    private:
        BLEConsole *_parent;
    };

    class RxCallbacks : public BLECharacteristicCallbacks
    {
    public:
        RxCallbacks(BLEConsole *parent);
        void onWrite(BLECharacteristic *pCharacteristic) override;

    private:
        BLEConsole *_parent;
    };
};
