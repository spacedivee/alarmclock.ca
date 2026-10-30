# Alarmclock.ca , A canadian outdoor designed alarm clock


<img width="1018" height="633" alt="allparts" src="https://github.com/user-attachments/assets/d27cf096-5acd-4874-9558-c322981a3c58" />


A custom-built digital alarm clock made for the [BLARE project by Hack Club](https://blare.hackclub.com/). 

## Overview

The goal of this project is to build a functional alarm clock using the BLARE kit, with a focus on embedded firmware, electronics integration, and mechanical design.

The clock is designed to display the current time and allow the user to configure and use an alarm. A rotary encoder provides an additional input method ( like to quickly change the time or navigate a menu quicker) , while a piezo buzzer provides the alarm sound.

The case and other systems were designed for outdoor/camping use.

## Features

- Digital clock displayed on a TFT screen.
- Alarm functionality with an audible buzzer.
- Rotary encoder for user input and navigation.
- Auxiliary battery pack with a physical power switch. (when not plugged in)
- A simple hook at the top to attach the clock to other things
- Slots for plexiglass or other transparent material to be attached to protect the TFT screen. 


## Project Photos

### Assembled Clock

*ill drop it once i actually get it and build it*



### Schematic

<img width="1000" height="675" alt="shcemtic" src="https://github.com/user-attachments/assets/416c32ae-f594-4e50-aec6-2392c65e80fb" />

### PCB Design
<img width="1000" height="676" alt="pcb" src="https://github.com/user-attachments/assets/c0086299-acad-4ceb-b505-468517a3d96d" />
*The PCB as seen on KiCad*
<img width="1000" height="600" alt="pcb 3d" src="https://github.com/user-attachments/assets/0426bf7f-6379-45d6-ad3e-1601038e9dfc" />
*The 3D Model*

### Enclosure and Assembly

<img width="1000" height="622" alt="allparts" src="https://github.com/user-attachments/assets/5bd35a1b-e5ad-4e6f-99b4-410fbacf42d7" />

*Full Build Assembly*

<img width="1000" height="719" alt="encloser" src="https://github.com/user-attachments/assets/e069508f-4ce8-45c5-a1b9-a806de9a6e59" />

*Case Body*

<img width="1000" height="540" alt="Lid" src="https://github.com/user-attachments/assets/379013b6-c7ea-4483-8b9a-5a8ad37eac26" />

*Lid*

## Hardware

The project uses the following components.

| Component | Purpose |
|---|---|
| Seeed XIAO ESP32C3 | Main microcontroller |
| 2.25-inch ST7789 TFT display | Displays the clock interface |
| 3.3 V piezo buzzer | Produces the alarm sound |
| Rotary encoder | User input |
| Auxiliary battery pack | Portable power supply |
| Physical power switch | Controls power to the clock |
| Custom PCB | Connects the electronic components |
| Custom enclosure | Houses and protects the assembly |

The BLARE kit also includes keyboard switches, keycaps, diodes, display headers, jumper wires, heat-set inserts, and mounting screws.

## Bill of Materials (BOM)

| Part | Quantity | Source |
|---|---:|---|
| Seeed XIAO ESP32C3 | 1 | BLARE kit |
| ST7789 TFT display | 1 | BLARE kit |
| 3.3 V piezo buzzer | 1 | BLARE kit |
| MX-style keyboard switches | 4 | BLARE kit |
| White DSA keycaps | 4 | BLARE kit |
| Display header and jumper wires | 1 | BLARE kit |
| Rotary encoder | 1 | Provided by me |
| Auxiliary battery pack | 1 | Provided by me |
| Power switch | 1 | Provided by me |
| Custom PCB | 1 | Designed in KiCad |

*The BOM lists the supplied kit components and additional hardware.*

## Firmware

The firmware is developed in the Arduino IDE for the Seeed XIAO ESP32C3.

To be implemented: sleep mode or something of the sort that reduces battery usage when not in use.
Add the license you choose for your firmware, PCB design, and CAD files. Make sure the license is appropriate for any third-party libraries or design assets included in the project.
