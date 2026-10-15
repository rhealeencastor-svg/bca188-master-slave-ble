# BCA 188: Master and Slave BLE

One ESP32-WROOM master controls the LEDs on two ESP32-S3 slaves through BLE. Hold the master's button to turn the LEDs on; release it to turn them off. A third slave sketch is included if needed.

[Lab instructions](https://jomvill.notion.site/BCA-188-Master-Slave-BLE-ESP32-f29c5d2c636e4019958866113371a94f)

## Materials

- 1 ESP32-WROOM development board
- 2 ESP32-S3 development boards
- 1 push button
- 2 LEDs and 2 × 330 Ω resistors
- USB data cables, jumper wires, and breadboards as needed

For a third slave, add one S3, LED, resistor, and USB cable.

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
| Slave 3 (optional) | [slave3.ino](slave3/slave3.ino) | ESP32S3 Dev Module |

Each slave file already has its own ID. Keep the sketches in their separate folders.

Install **esp32 by Espressif Systems** in Arduino IDE's Boards Manager. These sketches use version **3.3.11** and its included BLE library.

Upload each file to the matching board and USB port. For an S3's native USB socket, enable **USB CDC On Boot** and select **Hardware CDC and JTAG**. For its COM/UART socket, disable **USB CDC On Boot**.

Power the boards and open the master's Serial Monitor at **115200 baud**. Wait for slaves 1 and 2 to connect, then try the button. They connect automatically; no Bluetooth pairing is needed. With two slaves, the master continues searching for the optional third.

## Team members

- Michael O. Cadiz
- Gazawe Casim
- Rhea Leen P. Castor
- Christine Gallarde

## Documentation

[Photos, demo, and lab response](docs/README.md)

The group's documentation will be uploaded here.
