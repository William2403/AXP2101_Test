#include "BleConsole.h"

BleConsole *BleConsole::instance = nullptr;

#define SERVICE_UUID "6e400001-b5a3-f393-e0a9-e50e24dcca9e"
#define RX_UUID "6e400002-b5a3-f393-e0a9-e50e24dcca9e"
#define TX_UUID "6e400003-b5a3-f393-e0a9-e50e24dcca9e"

bool BleConsole::begin(const char *deviceName)
{
    instance = this;

    NimBLEDevice::init(deviceName);
    NimBLEServer *server = NimBLEDevice::createServer();
    NimBLEService *service = server->createService(SERVICE_UUID);

    txChar = service->createCharacteristic(
        TX_UUID,
        NIMBLE_PROPERTY::NOTIFY);

    NimBLECharacteristic *rxChar = service->createCharacteristic(
        RX_UUID,
        NIMBLE_PROPERTY::WRITE);

    rxChar->setCallbacks(new RxCallbacks());

    service->start();
    NimBLEAdvertising *adv = NimBLEDevice::getAdvertising();
    adv->addServiceUUID(SERVICE_UUID);
    adv->start();

    return true;
}

void BleConsole::registerCommand(const String &cmd, BleCmdHandler handler)
{
    handlers[cmd] = handler;
}

void BleConsole::println(const String &msg)
{
    if (!txChar)
        return;
    txChar->setValue(msg.c_str());
    txChar->notify();
}

void BleConsole::handleRx(const String &cmd)
{
    String response;
    auto it = handlers.find(cmd);

    if (it != handlers.end())
    {
        it->second(cmd, response);
    }
    else
    {
        response = "Unknown command\n";
    }

    println(response);
}

void BleConsole::RxCallbacks::onWrite(NimBLECharacteristic *c)
{
    if (!instance)
        return;
    std::string v = c->getValue();
    instance->handleRx(String(v.c_str()));
}
