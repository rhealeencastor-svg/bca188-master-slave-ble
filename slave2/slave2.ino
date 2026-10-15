#include <Arduino.h>
#include <BLEDevice.h>
#include <atomic>

const int SLAVE_ID = 2;
const int LED_PIN = 4;
const char *SERVICE_UUIDS[] = {
  "2b92513e-afed-40ac-afa6-e54c63acdceb",
  "2b92513e-afed-40ac-afa6-e54c63acdcec",
  "2b92513e-afed-40ac-afa6-e54c63acdced"
};
const char *CHAR_UUID = "ea3d7c32-0013-4447-8f7b-47b959b5cddc";
static_assert(SLAVE_ID >= 1 && SLAVE_ID <= 3, "SLAVE_ID must be 1, 2, or 3");

std::atomic<bool> connected(false);
std::atomic<bool> requestedOn(false);
std::atomic<bool> restartAdvertising(false);
bool ledOn = false;

class ServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *server) override {
    connected = true;
    Serial.println("Connected");
  }

  void onDisconnect(BLEServer *server) override {
    connected = false;
    requestedOn = false;
    restartAdvertising = true;
    Serial.println("Disconnected");
  }
};

class LedCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *characteristic) override {
    String value = characteristic->getValue();
    if (value == "1") requestedOn = true;
    if (value == "0") requestedOn = false;
  }
};

ServerCallbacks serverCallbacks;
LedCallbacks ledCallbacks;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  BLEDevice::init(String("BCA188 Slave ") + SLAVE_ID);
  Serial.printf("Slave %d MAC: ", SLAVE_ID);
  Serial.println(BLEDevice::getAddress().toString().c_str());

  BLEServer *server = BLEDevice::createServer();
  server->setCallbacks(&serverCallbacks);
  BLEService *service = server->createService(SERVICE_UUIDS[SLAVE_ID - 1]);
  BLECharacteristic *characteristic = service->createCharacteristic(
    CHAR_UUID, BLECharacteristic::PROPERTY_WRITE);
  characteristic->setCallbacks(&ledCallbacks);
  characteristic->setValue("0");
  service->start();

  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_UUIDS[SLAVE_ID - 1]);
  advertising->setScanResponse(true);
  BLEDevice::startAdvertising();
  Serial.println("Advertising");
  Serial.println("LED OFF");
}

void loop() {
  bool on = connected.load() && requestedOn.load();
  if (on != ledOn) {
    ledOn = on;
    digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
    Serial.println(ledOn ? "LED ON" : "LED OFF");
  }

  if (restartAdvertising.exchange(false)) {
    delay(200);
    if (!connected.load()) {
      BLEDevice::startAdvertising();
      Serial.println("Advertising");
    }
  }
  delay(5);
}
