# Laboratory Activity 7: Master-Slave BLE Communication (ESP32)

We used one ESP32-WROOM as the master and three ESP32-S3 boards as slaves. Holding the master's button turns the slave LEDs on, and releasing it turns them off through BLE.

**Group name:** CCCG

[Lab instructions](https://jomvill.notion.site/BCA-188-Master-Slave-BLE-ESP32-f29c5d2c636e4019958866113371a94f)

## Materials

- 1 ESP32-WROOM development board
- 3 ESP32-S3 development boards
- 1 push button
- 3 LEDs and 3 × 330 Ω resistors
- 4 USB data cables, jumper wires, and breadboards as needed

## Connections

| Board | Connection |
| --- | --- |
| Master | GPIO 18 → button → GND |
| Each slave | GPIO 4 → 330 Ω resistor → LED long leg (+) |
| Each slave | LED short leg (−) → its own GND |

We powered each board through USB. Each LED circuit uses its own board's GND. The boards communicate wirelessly through BLE.

## Programs

| Board | File | Arduino board |
| --- | --- | --- |
| Master | [master.ino](master/master.ino) | ESP32 Dev Module |
| Slave 1 | [slave.ino](slave/slave.ino) | ESP32S3 Dev Module |
| Slave 2 | [slave2.ino](slave2/slave2.ino) | ESP32S3 Dev Module |
| Slave 3 | [slave3.ino](slave3/slave3.ino) | ESP32S3 Dev Module |

Each slave sketch has its own ID and service UUID. The master scans for these services and connects to the detected slave addresses.

The sketches use **esp32 by Espressif Systems 3.3.11** and its included BLE library in Arduino IDE.

Serial Monitor runs at **115200 baud**. The slaves connect to the master automatically.

## Team members

| Member | Board role | What they worked on |
| --- | --- | --- |
| Michael O. Cadiz | Slave 1 | Slave device and testing |
| Gazawe Casim | Slave 2 | Slave device and testing |
| Rhea Leen P. Castor | Master | Programming, wiring, and testing |
| Christine Gallarde | Slave 3 | Slave device, testing, and video recording |

## Documentation

- [Wiring diagram for the master and all three slaves](docs/wiring.svg)
- [Setup photos and test records](docs/README.md)
- [Demo video](https://drive.google.com/file/d/1kcCcMRImZBvdQX3uAcBArwu-nvJS5H2h/view?usp=sharing)

Our documentation includes the wiring, setup photos, and timestamps for the Serial Monitor output in our video.
