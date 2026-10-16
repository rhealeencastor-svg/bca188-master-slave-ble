# Laboratory Activity 7: Master-Slave BLE Communication (ESP32)

One ESP32-WROOM master controls the LEDs on three ESP32-S3 slaves through BLE. Hold the master's button to turn the LEDs on; release it to turn them off.

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

Power each board through USB. If using a breadboard, connect the board's GND to its ground rail. This circuit does not need a 3V3 connection or wires between boards.

## Programs

| Board | File | Arduino board |
| --- | --- | --- |
| Master | [master.ino](master/master.ino) | ESP32 Dev Module |
| Slave 1 | [slave.ino](slave/slave.ino) | ESP32S3 Dev Module |
| Slave 2 | [slave2.ino](slave2/slave2.ino) | ESP32S3 Dev Module |
| Slave 3 | [slave3.ino](slave3/slave3.ino) | ESP32S3 Dev Module |

Each slave file already has its own ID. Keep the sketches in their separate folders.

Install **esp32 by Espressif Systems** in Arduino IDE's Boards Manager. These sketches use version **3.3.11** and its included BLE library.

Upload each file to the matching board and USB port. For an S3's native USB socket, enable **USB CDC On Boot** and select **Hardware CDC and JTAG**. For its COM/UART socket, disable **USB CDC On Boot**.

Power the boards and open the master's Serial Monitor at **115200 baud**. Wait for slaves 1, 2, and 3 to connect, then try the button. They connect automatically; no Bluetooth pairing is needed.

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

The video includes Serial Monitor output. See the documentation for timestamps and the remaining records to add.

Each member submits this repository URL in MOLÉ.
