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

The [demo video](https://drive.google.com/file/d/1kcCcMRImZBvdQX3uAcBArwu-nvJS5H2h/view?usp=sharing) includes these views:

- Around 0:25: the master shows slave connection messages and LED OFF commands.
- Around 0:42: the final demonstration begins.
- Around 1:01: a slave's Serial Monitor shows repeated LED ON and LED OFF messages.

Separate, clearly labelled Serial Monitor screenshots for the master and each numbered slave still need to be uploaded.

## BLE addresses and UUIDs

Each sketch prints its BLE MAC address at startup. The four full addresses have not been transcribed from the recording. Copy the exact startup values below; they do not need to be hardcoded in the programs.

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

The video is shared with anyone who has the link; no sign-in is required.

## Results

The group completed the setup with one master and three slaves. The setup photos show the red, blue, and yellow slave LEDs lit. The final demonstration starts around 0:42, and the slave monitor near 1:01 shows ON/OFF responses.

The separate initial connection/message test with one slave still needs its own record.

## Team photos

![Team photo 1](849211076_1357894819755009_187354605431563643_n.jpg)

![Team photo 2](849908240_1588358622975638_2266061245060579666_n.jpg)

## Lab response

**How is the stored and analyzed data used?**

Stored data can help identify patterns and guide decisions or automation. In this setup, the master only sends the current button state to the slaves to control their LEDs. The programs do not store readings or analyze data.
