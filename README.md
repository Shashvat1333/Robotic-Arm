# Robotic Arm Project

A robotic arm I built from scratch that you control wirelessly with a Bluetooth controller, using an ESP32 board.

<img width="616" height="752" alt="image" src="https://github.com/user-attachments/assets/9ddec064-8fc9-424b-8597-676401248a46" />


## Table of Contents
- [Overview](#overview)
- [Repository Structure](#repository-structure)
- [CAD Model & Assembly](#cad-model--assembly)
- [Schematic & Wiring](#schematic--wiring)
- [Firmware](#firmware)
- [Getting Started](#getting-started)
- [Bill of Materials (BOM)](#bill-of-materials-bom)
- [License](#license)

## Overview

I wanted to build a robotic arm that actually works, not just a model that sits there. So this project covers everything: designing the parts, printing them, wiring up the electronics, and writing the code that makes it move.

I did every part of this myself. I sketched out how the arm should move, I created gear boxes for my servo so they have enough strength to hold their position under load, and then had to go back and redesign a few parts more than once when they didn't fit right or weren't strong enough. Instead of buying a kit, I built this piece by piece so I understood exactly why each part works the way it does.

### What it does

- **Custom parts:** I designed the gears, joints, and brackets myself in Onshape, making sure everything had enough clearance to actually fit together once printed.
- **Wireless control:** An ESP32 board runs Bluepad32, which lets it read input from a normal Bluetooth controller and turn that into arm movement.
- **Safe wiring for high current:** The servos pull a lot of power, so I moved away from a breadboard (which can't handle that much current safely) and decided to solder a proper perfboard with thick power and ground lines instead.

---

## Repository Structure 

```
robotic-arm-project/
├── CAD/ # .step files for every 3D printed part
├── Firmware/ # ESP32 code (FIRMWARE.ino)
├── Wiring Diagrams.md # How everything is wired
├── BOM.csv # Full parts list with prices
├── JOURNAL.md # My build log, day by day
├── LICENSE.md
└── README.md
```

---

## CAD Model & Assembly

I modeled every joint and structural piece in Onshape, paying close attention to how the parts would actually fit together once printed, not just how they looked on screen. This let me test gear ratios and pivot points digitally before wasting filament on parts that wouldn't work. All the finished, ready to print parts are in the [CAD](https://github.com/Shashvat1333/Robotic-Arm/tree/main/CAD) folder as `.step` files.

To assemble the frame, I melted heat set inserts into the printed plastic with a soldering iron. This gives the M3/M2 bolts real metal threads to grip instead of just biting into plastic, which means the joints won't strip out over time and I can still take things apart later if I need to fix something.

---

## Schematic & Wiring

I didn't use a manufactured PCB for this. Instead everything is wired on a soldered perfboard, because the servos pull a lot of current and a normal breadboard just can't handle that safely without overheating or dropping voltage.

The full wiring breakdown is in [Wiring Diagrams.md](https://github.com/Shashvat1333/Robotic-Arm/blob/main/Wiring%20Diagram.md), but here's the short version:

| Component | ESP32 GPIO (Signal) | Power (+) | Ground (–) |
|---|---|---|---|
| Servo 1 – Base (MG90S) | GPIO 13 | Perfboard + bus line | Perfboard – bus line |
| Servo 2 – Shoulder (MG90S) | GPIO 12 | Perfboard + bus line | Perfboard – bus line |
| Servo 3 – Elbow (MG90S| GPIO 14 | Perfboard + bus line | Perfboard – bus line |
| Servo 4 – Wrist Pitch (MG90S) | GPIO 27 | Perfboard + bus line | Perfboard – bus line |
| Servo 5 – Wrist Roll (MG90S) | GPIO 26 | Perfboard + bus line | Perfboard – bus line |
| Servo 6 – Gripper (MG90S) | GPIO 25 | Perfboard + bus line | Perfboard – bus line |
| ESP32 Board | — | VIN pin connected to + bus | GND pin connected to – bus |
| Power Supply | — | 5V DC Adapter (+) | 5V DC Adapter (–) |

---

## Firmware

The code is written in C++ using the Arduino framework. It uses the `ESP32Servo` and `Bluepad32` libraries to take input from a Bluetooth controller and turn the joystick and trigger positions into servo movement. It's always listening for a paired controller, and once one connects it reads the stick positions and sends the right PWM signal to each servo.

- **Code:** [FIRMWARE.ino](https://github.com/Shashvat1333/Robotic-Arm/blob/main/FIRMWARE.ino)
- **Libraries you need:** `ESP32Servo`, `Bluepad32`
- **Board:** ESP32 Dev Module

---

## Getting Started

Here's how to build this yourself:

1. **Print the parts** — Grab the `.step` files from the [CAD](https://github.com/Shashvat1333/Robotic-Arm/tree/main/CAD) folder and slice them. I used PLA for mine.
2. **Put the frame together** — Melt the M3/M2 heat set inserts into the printed parts with a soldering iron, then bolt everything together following the CAD model.
3. **Wire it up** — Follow [Wiring Diagrams.md](https://github.com/Shashvat1333/Robotic-Arm/blob/main/Wiring%20Diagram.md) to connect the servos, ESP32, and power supply through the perfboard.
4. **Upload the firmware** — Open [FIRMWARE.ino](https://github.com/Shashvat1333/Robotic-Arm/blob/main/FIRMWARE.ino) in the Arduino IDE, install the `ESP32Servo` and `Bluepad32` libraries, pick the ESP32 Dev Module board, and hit upload.
5. **Pair a controller** — Turn the arm on, pair a Bluetooth controller, and you're good to go.

---

## Bill of Materials (BOM)

| Item | Qty | Supplier | Cost/item | Total Cost | Link |
| :--- | :---: | :--- | :---: | :---: | :--- |
| MG90S Servo | 1 | AliExpress | $12.08 | $12.08 | [Link](https://www.aliexpress.com/item/1005006883748786.html) |
| PLA 1kg | 1 | Amazon | $16.78 | $16.78 | [Link](https://www.amazon.ca/ELEGOO-Filament-Identification-Compatible-Dimensional/dp/B0FZVLHDSQ) |
| Soft Silicon Wire | 2 | AliExpress | $3.50 | $7.00 | [Link](https://www.aliexpress.com/item/1005006441248773.html) |
| ESP32-32D | 1 | AliExpress | $5.77 | $5.77 | [Link](https://www.aliexpress.com/item/1005007820190456.html) |
| M3 Brass Insert Nut and Stainless Steel Screw Kit | 1 | AliExpress | $15.31 | $15.31 | [Link](https://www.aliexpress.com/item/1005008394979732.html) |
| M2 Heat Inserts | 1 | AliExpress | $3.25 | $3.25 | [Link](https://www.aliexpress.com/item/32890237459.html) |
| M2 M2.5 M3 KM Screw Flat Head Phillips Screws Kit | 1 | AliExpress | $4.32 | $4.32 | [Link](https://www.aliexpress.com/item/4000056753202.html) |
| Estimated total shipping | 1 | - | $0.00 | $0.00 | - |
| **Total** | | | | **$64.51** | |

Full breakdown in [BOM.csv](https://github.com/Shashvat1333/Robotic-Arm/blob/main/BOM.csv).

---

## License

This project is licensed under the terms in [LICENSE.md](https://github.com/Shashvat1333/Robotic-Arm/blob/main/LICENSE.md).
