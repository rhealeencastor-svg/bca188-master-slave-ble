#include <Arduino.h>
#include <BLEDevice.h>
#include <atomic>

const int BUTTON_PIN = 18;
const char *SERVICE_UUIDS[] = {
  "2b92513e-afed-40ac-afa6-e54c63acdceb",
  "2b92513e-afed-40ac-afa6-e54c63acdcec",
  "2b92513e-afed-40ac-afa6-e54c63acdced"
};
const char *CHAR_UUID = "ea3d7c32-0013-4447-8f7b-47b959b5cddc";

struct Slave {
  BLEClient *client = nullptr;
  BLERemoteCharacteristic *led = nullptr;
  int sentState = -1;
};

Slave slaves[3];
BLEScan *scan;
std::atomic<bool> scanReady(false);
unsigned long lastScan = 0;
bool lastReading = false;
bool pressed = false;
unsigned long changedAt = 0;

void scanFinished(BLEScanResults results) {
  scanReady = true;
}

void connectSlaves() {
  BLEScanResults *results = scan->getResults();
  if (results == nullptr) return;

  for (int i = 0; i < results->getCount(); i++) {
    BLEAdvertisedDevice device = results->getDevice(i);
    if (!device.haveServiceUUID()) continue;

    for (int n = 0; n < 3; n++) {
      Slave &slave = slaves[n];
      if (slave.client->isConnected() ||
          !device.isAdvertisingService(BLEUUID(SERVICE_UUIDS[n]))) continue;

      Serial.printf("Connecting slave %d...\n", n + 1);
      slave.led = nullptr;
      if (!slave.client->connect(device.getAddress(), device.getAddressType(), 5000)) {
        Serial.printf("Slave %d connection failed\n", n + 1);
        break;
      }

      // Refresh handles after a slave restarts.
      slave.client->getServices();
      BLERemoteService *service = slave.client->getService(SERVICE_UUIDS[n]);
      slave.led = service ? service->getCharacteristic(BLEUUID(CHAR_UUID)) : nullptr;

      if (slave.led && slave.led->canWrite() && slave.client->isConnected()) {
        slave.sentState = -1;
        Serial.printf("Slave %d connected\n", n + 1);
      } else {
        Serial.printf("Slave %d LED characteristic not found\n", n + 1);
        slave.led = nullptr;
        slave.client->disconnect();
      }
      break;
    }
  }
  scan->clearResults();
  lastReading = pressed = digitalRead(BUTTON_PIN) == LOW;
  changedAt = millis();
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lastReading = pressed = digitalRead(BUTTON_PIN) == LOW;
  BLEDevice::init("BCA188 Master");
  Serial.print("Master MAC: ");
  Serial.println(BLEDevice::getAddress().toString().c_str());
  for (Slave &slave : slaves) slave.client = BLEDevice::createClient();
  scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  scan->setInterval(100);
  scan->setWindow(80);
  lastScan = millis() - 3000;
}

void loop() {
  bool reading = digitalRead(BUTTON_PIN) == LOW;
  if (reading != lastReading) {
    lastReading = reading;
    changedAt = millis();
  }

  if (millis() - changedAt >= 30) {
    pressed = reading;
  }

  bool missingSlave = false;
  for (int n = 0; n < 3; n++) {
    Slave &slave = slaves[n];
    if (!slave.client->isConnected()) {
      if (slave.led) Serial.printf("Slave %d disconnected\n", n + 1);
      slave.led = nullptr;
      missingSlave = true;
      continue;
    }

    if (slave.led && slave.sentState != pressed) {
      uint8_t value = pressed ? '1' : '0';
      if (slave.led->writeValue(&value, 1, true)) {
        slave.sentState = pressed;
        Serial.printf("Slave %d LED %s\n", n + 1, pressed ? "ON" : "OFF");
      } else {
        Serial.printf("Slave %d write failed; reconnecting\n", n + 1);
        slave.led = nullptr;
        slave.client->disconnect();
        missingSlave = true;
      }
    }
  }

  if (scanReady.exchange(false)) {
    connectSlaves();
  } else if (missingSlave && !scan->isScanning() && millis() - lastScan >= 3000) {
    lastScan = millis();
    Serial.println("Scanning...");
    scan->start(2, scanFinished, false);
  }
  delay(5);
}
