#include "BLEConsole.h"

// UUIDs tipo Nordic UART (estándar de facto)
#define SERVICE_UUID "6e400001-b5a3-f393-e0a9-e50e24dcca9e"
#define RX_UUID "6e400002-b5a3-f393-e0a9-e50e24dcca9e"
#define TX_UUID "6e400003-b5a3-f393-e0a9-e50e24dcca9e"

BLEConsole::BLEConsole(const char *deviceName)
    : _deviceName(deviceName) {}

void BLEConsole::begin()
{
    BLEDevice::init(_deviceName);

    BLEServer *server = BLEDevice::createServer();
    server->setCallbacks(new ServerCallbacks(this));

    BLEService *service = server->createService(SERVICE_UUID);

    _txChar = service->createCharacteristic(
        TX_UUID,
        BLECharacteristic::PROPERTY_NOTIFY);
    _txChar->addDescriptor(new BLE2902());

    BLECharacteristic *rxChar = service->createCharacteristic(
        RX_UUID,
        BLECharacteristic::PROPERTY_WRITE);
    rxChar->setCallbacks(new RxCallbacks(this));

    service->start();

    BLEAdvertising *advertising = BLEDevice::getAdvertising();
    advertising->addServiceUUID(SERVICE_UUID);
    advertising->start();

    Serial.println("BLEConsole lista 🚀");
}

void BLEConsole::send(const String &msg)
{
    if (_deviceConnected && _txChar)
    {
        _txChar->setValue(msg.c_str());
        _txChar->notify();
    }
}

void BLEConsole::onCommand(void (*callback)(String))
{
    _userCallback = callback;
}

/* ===== Server Callbacks ===== */

BLEConsole::ServerCallbacks::ServerCallbacks(BLEConsole *parent)
    : _parent(parent) {}

void BLEConsole::ServerCallbacks::onConnect(BLEServer *pServer)
{
    _parent->_deviceConnected = true;
    Serial.println("📱 Celular CONECTADO");
}

void BLEConsole::ServerCallbacks::onDisconnect(BLEServer *pServer)
{
    _parent->_deviceConnected = false;
    Serial.println("📱 Celular DESCONECTADO");
    pServer->startAdvertising();
}

/* ===== RX Callbacks ===== */

BLEConsole::RxCallbacks::RxCallbacks(BLEConsole *parent)
    : _parent(parent) {}

void BLEConsole::RxCallbacks::onWrite(BLECharacteristic *pCharacteristic)
{
    std::string value = pCharacteristic->getValue();
    if (!value.length())
        return;

    String cmd;
    for (char c : value)
        cmd += c;

    Serial.print("📥 CMD: ");
    Serial.println(cmd);

    if (_parent->_userCallback)
    {
        _parent->_userCallback(cmd);
    }
}
