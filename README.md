# BCA 188 · Master & Slave BLE

Two ESP32 boards: hold the master's button to turn on the slave's LED. Release it to turn the LED off.

Based on the [lab page](https://jomvill.notion.site/BCA-188-Master-Slave-BLE-ESP32-f29c5d2c636e4019958866113371a94f). The master is a BLE client; the slave is a BLE server.

## Materials

- 2 original ESP32-WROOM-32 development boards
- 2 USB data cables matching the boards
- 1 momentary push button
- 1 LED
- 1 330 Ω resistor
- 1–2 breadboards
- Jumper wires
- Computer with Arduino IDE

## Wiring

**Master:** GPIO 18 → button → GND. The code uses the internal pull-up resistor.

**Slave:** GPIO 19 → 330 Ω resistor → LED anode (long leg). LED cathode (short leg) → GND.

Use each board's own GND. The boards communicate wirelessly; no wires are needed between them. Do not connect either GPIO to 5 V. If the button has four legs, use contacts that connect only when pressed.

## Upload

1. Install Arduino IDE. In Preferences, add this board manager URL:

   `https://espressif.github.io/arduino-esp32/package_esp32_index.json`

2. In Boards Manager, install **esp32 by Espressif Systems**, version **3.3.11**. The BLE library is included.
3. Connect the slave. Open `slave/slave.ino`, select **ESP32 Dev Module** and its port, then upload.
4. Connect the master. Open `master/master.ino`, select **ESP32 Dev Module** and its port, then upload.
5. Open Serial Monitor at **115200 baud** to check the connection messages. Hold the button, then release it.

If upload stays at “Connecting…”, hold BOOT until writing starts, then release it. If no port appears, check the cable and the board's USB driver.

Both sketches use the same service and characteristic UUIDs. Leave them matching. No UUID generator or hardcoded Bluetooth address is needed. If other pairs nearby use this code, give your pair different UUIDs in both files.

You can edit the folder in VS Code and upload through Arduino IDE. No VS Code extension is required.

## Check it on the boards

- With both boards powered, confirm that the master connects to the slave.
- Hold the button: the slave LED should turn on.
- Release the button: the LED should turn off.
- Repeat a few times and confirm that each press and release works.
- Restart either board and confirm that the connection returns.
- Turn off the master: the slave LED should turn off after the connection times out, which can take a few seconds.

Both sketches compile for ESP32 Dev Module with Espressif core 3.3.11. A real two-board test is still needed.

The short lab answers are in [answers.md](answers.md).
