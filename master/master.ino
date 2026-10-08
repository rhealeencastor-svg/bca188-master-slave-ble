#include <Arduino.h>
#include <BLEDevice.h>

const int BUTTON_PIN = 18;
const char *SERVICE_UUID = "2b92513e-afed-40ac-afa6-e54c63acdceb";
const char *CHAR_UUID = "ea3d7c32-0013-4447-8f7b-47b959b5cddc";

BLEClient *client;
BLEScan *scan;
BLERemoteCharacteristic *led = nullptr;
bool lastReading = false;
bool pressed = false;
unsigned long changedAt = 0;
int sentState = -1;

void connectToSlave() {
  Serial.println("Scanning...");
  BLEScanResults *results = scan->start(2, false);
  if (results == nullptr) return;

  for (int i = 0; i < results->getCount(); i++) {
    BLEAdvertisedDevice device = results->getDevice(i);
    if (!device.haveServiceUUID() ||
        !device.isAdvertisingService(BLEUUID(SERVICE_UUID))) continue;

    Serial.println("Connecting...");
    if (!client->connect(device.getAddress(), device.getAddressType(), 5000)) {
      Serial.println("Connection failed");
      break;
    }

    // Refresh handles in case the slave restarted.
    client->getServices();
    BLERemoteService *service = client->getService(SERVICE_UUID);
    led = service ? service->getCharacteristic(BLEUUID(CHAR_UUID)) : nullptr;

    if (led && led->canWrite() && client->isConnected()) {
      Serial.println("Connected");
      lastReading = pressed = digitalRead(BUTTON_PIN) == LOW;
      changedAt = millis();
      sentState = -1;
    } else {
      Serial.println("LED characteristic not found");
      led = nullptr;
      client->disconnect();
    }
    break;
  }
  scan->clearResults();
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lastReading = pressed = digitalRead(BUTTON_PIN) == LOW;
  BLEDevice::init("BCA188 Master");
  Serial.print("Master MAC: ");
  Serial.println(BLEDevice::getAddress().toString().c_str());
  client = BLEDevice::createClient();
  scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  scan->setInterval(100);
  scan->setWindow(80);
}

void loop() {
  if (!client->isConnected()) {
    if (led) Serial.println("Disconnected");
    led = nullptr;
    connectToSlave();
    delay(50);
    return;
  }

  bool reading = digitalRead(BUTTON_PIN) == LOW;
  if (reading != lastReading) {
    lastReading = reading;
    changedAt = millis();
  }

  if (millis() - changedAt >= 30) {
    pressed = reading;
    if (led && sentState != pressed) {
      uint8_t value = pressed ? '1' : '0';
      if (led->writeValue(&value, 1, true)) {
        sentState = pressed;
        Serial.println(pressed ? "LED ON" : "LED OFF");
      } else {
        Serial.println("Write failed; reconnecting");
        led = nullptr;
        client->disconnect();
      }
    }
  }
  delay(5);
}
