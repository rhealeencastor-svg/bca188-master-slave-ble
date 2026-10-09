# BCA 188 · Master & Slave BLE

One ESP32-WROOM master and three ESP32-S3 slaves. Hold the master's button to turn on all three LEDs. Release it to turn them off.

Based on the [lab page](https://jomvill.notion.site/BCA-188-Master-Slave-BLE-ESP32-f29c5d2c636e4019958866113371a94f). The master is a BLE client; the slave is a BLE server.

## Materials

- 1 ESP32-WROOM-32 development board
- 3 ESP32-S3 development boards with GPIO4 available
- 4 USB data cables matching the boards
- 1 momentary push button
- 3 LEDs
- 3 × 330 Ω resistors
- 4 breadboards recommended
- Jumper wires
- Computer with Arduino IDE
- USB power for all four boards

## Wiring

**Master:** GPIO 18 → button → GND. The code uses the internal pull-up resistor.

**Each slave:** GPIO 4 → 330 Ω resistor → LED anode (long leg). LED cathode (short leg) → GND.

Use each board's own GND. The boards communicate wirelessly; no wires are needed between them. Do not connect either GPIO to 5 V. If the button has four legs, use contacts that connect only when pressed.

## Upload

1. Install Arduino IDE. In Preferences, add this board manager URL:

   `https://espressif.github.io/arduino-esp32/package_esp32_index.json`

2. In Boards Manager, install **esp32 by Espressif Systems**, version **3.3.11**. The BLE library is included.
3. Connect only the first S3 to the computer. Open `slave/slave.ino`. Select **ESP32S3 Dev Module** and its port. Leave `SLAVE_ID = 1`, then upload. Label that board 1.
4. Connect the second S3. Change `SLAVE_ID` to `2`, select its port, and upload. Label it 2.
5. Connect the third S3. Change `SLAVE_ID` to `3`, select its port, and upload. Label it 3. Do not upload the same ID to multiple slaves.
6. Connect the WROOM master. Open `master/master.ino`, select **ESP32 Dev Module** and its port, then upload.
7. Power all four boards. Open the master's Serial Monitor at **115200 baud**. Press RESET/EN if you missed the startup messages. Wait for `Slave 1 connected`, `Slave 2 connected`, and `Slave 3 connected`.
8. Hold the master's button: all three LEDs should turn on. Release it: all three should turn off.

For an S3 connected through its native USB port, set **USB CDC On Boot → Enabled** and **USB Mode → Hardware CDC and JTAG**. If you use a separate USB-to-UART port, leave USB CDC On Boot disabled so the serial messages use UART instead.

If upload stays at “Connecting…”, hold BOOT until writing starts, then release it. If no port appears, check the cable and the board's USB driver.

Each slave ID selects a different service UUID; the master already knows all three. Leave the UUID lists matching in both files. No hardcoded MAC address or pairing in the computer's Bluetooth settings is needed. If another group nearby uses this code, use a different UUID set in both files.

You can edit the folder in VS Code and upload through Arduino IDE. No VS Code extension is required.

## Check it on the boards

- With all four boards powered, confirm that the master connects to all three slaves.
- Hold the button: all three slave LEDs should turn on.
- Release the button: all three LEDs should turn off.
- Repeat a few times and confirm that each press and release works.
- Restart any slave and confirm that it reconnects. Its LED should match the button's current state.
- Restart the master and confirm that all three reconnect.
- Turn off the master: the slave LEDs should turn off after the connections time out, which can take a few seconds.

Both sketches compile with Espressif core 3.3.11: the master for ESP32 Dev Module, and the slave for ESP32S3 Dev Module with native USB enabled. A physical four-board test is still needed.

The short lab answers are in [answers.md](answers.md).
