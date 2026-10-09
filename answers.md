# Lab answers

**What materials are needed?**

One ESP32-WROOM-32 master, three ESP32-S3 slaves, four USB data cables, one button, three LEDs, three 330 Ω resistors, breadboards, jumper wires, USB power, and a computer with Arduino IDE.

**Are the original steps complete?**

No. The page mixes Bluetooth Classic and BLE, leaves out the connection procedure, and uses `available()` to check incoming data instead of connection status. It also needs exact wiring and code for the button and LED. This repository supplies a BLE version of that activity.

**How is the stored and analyzed data used?**

Sensor readings can be stored to find patterns and help automate devices, such as turning on a fan when temperature rises. In this lab, the master sends the button state to three slaves, which use it to control their LEDs. The sketches do not store readings or perform data analysis.
