# Documentation

## Circuit interface

![Master and three slave wiring](wiring.svg)

This diagram follows the GPIO pins used in the sketches. Each board is powered by USB and uses its own GND.

## Setup photos

![Group setup](IMG_5468.jpg)

![Red slave LED and Serial Monitor](IMG_5484.jpg)

![Blue slave LED and Serial Monitor](IMG_5485.jpg)

![Yellow slave LED and Serial Monitor](IMG_5486.jpg)

## Serial Monitor records

The setup photos include laptop screens, but clear screenshots are still needed for each board. Label each screenshot with its board role and capture both ON and OFF actions at 115200 baud.

| Board | Required output | Screenshot |
| --- | --- | --- |
| Master | Connections to slaves 1, 2, and 3; LED ON/OFF commands | To be uploaded |
| Slave 1 | Its ID/MAC, connection, LED ON and LED OFF | To be uploaded |
| Slave 2 | Its ID/MAC, connection, LED ON and LED OFF | To be uploaded |
| Slave 3 | Its ID/MAC, connection, LED ON and LED OFF | To be uploaded |

Also record the initial message/command test with one slave before the full three-slave test.

## BLE addresses and UUIDs

Each sketch prints its BLE MAC address when it starts. Open Serial Monitor at 115200 baud and press RESET/EN to capture it.

| Board | BLE MAC address |
| --- | --- |
| Master | To be recorded |
| Slave 1 | To be recorded |
| Slave 2 | To be recorded |
| Slave 3 | To be recorded |

The master scans for the service UUIDs, then connects using each discovered slave's BLE address. The slave names are BCA188 Slave 1, BCA188 Slave 2, and BCA188 Slave 3.

| Item | UUID |
| --- | --- |
| Slave 1 service | `2b92513e-afed-40ac-afa6-e54c63acdceb` |
| Slave 2 service | `2b92513e-afed-40ac-afa6-e54c63acdcec` |
| Slave 3 service | `2b92513e-afed-40ac-afa6-e54c63acdced` |
| LED characteristic, same on each slave | `ea3d7c32-0013-4447-8f7b-47b959b5cddc` |

The commands are `1` for ON and `0` for OFF.

## Demo

[Watch the system in operation](https://drive.google.com/file/d/1kcCcMRImZBvdQX3uAcBArwu-nvJS5H2h/view?usp=sharing)

Check that the instructor has viewing access.

## Results

The group reports completing the setup with one master and three slaves. The uploaded photos show the red, blue, and yellow slave LEDs lit.

| Test | Result and evidence |
| --- | --- |
| Initial connection/message test with one slave | To be recorded |
| Button held with one slave connected | To be recorded |
| Button released with one slave connected | To be recorded |
| Button held with all three slaves connected | Add the matching Serial Monitor screenshots and video timestamp |
| Button released with all three slaves connected | To be recorded |

## Team photos

![Team photo 1](849211076_1357894819755009_187354605431563643_n.jpg)

![Team photo 2](849908240_1588358622975638_2266061245060579666_n.jpg)

## Lab response

**How is the stored and analyzed data used?**

Stored data can help identify patterns and guide decisions or automation. In this setup, the master only sends the current button state to the slaves to control their LEDs. The programs do not store readings or analyze data.
