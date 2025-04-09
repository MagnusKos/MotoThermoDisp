# MotoThermoDisp
Just a small thing that provides an additional data about your motorbike.

## About the Project
Initially, this project designed for such motorcycles as "Minsk C4-300" and "ZiD Stayer 300-01", but it can be used on any other.
These motorbikes have the indicator of an engine overheating, but it is not in use, so as the temperature sensor.
Commercially available aftermarket indicators are too bulky and ugly, so the author decided to make a small and a simple device,
that will be a prettier version of commercial ones. Kinda. We'll see...
The project is based on cheap arduino compatible controllers and displays.

### Built with
![PlatformIO](https://shields.io/badge/PlatformIO-E37B0D?style=flat&logo=platformio&logoColor=white)
![CPlusPlus](https://img.shields.io/badge/-C++-blue?logo=cplusplus)
![CalVer](https://img.shields.io/badge/calver-YYYY.0M.0D-22bfda.svg)

### Compatible boards
- [x] _Maple Mini with STM32F103_: works fine, this is the main board for this project.
- [x] _ESP32S3 N16R8_: seems like it works, but not so sure.
- [ ] _Arduino Nano with ATmega328p_: the code is too bulky for this unit and it eats up all of the RAM. For now.

### Project structure
- _firmware_: catalogue with platformio subproject, contains software implementation
- _model_: catalogue with FreeCad subproject, contains 3D model of the case
- _electronics_: catalogue with kicad subproject, contains schematics and pcb

## Capabilities
- [x] Engine temperature indication
- [x] On-board voltage indication
- [x] Air temperature indication
- [x] Ready-to-go state indication
- [x] Overheating indication
- [ ] Temperature bar-graph
- [x] Screen selectors
- [ ] Overheating output (additional LEDs, fans, locomotive air horns, etc)

## Known issues
- _Display blinks on update event_. It's not a bug, it's a feature. Just kidding. I'll rework this process later.
- _Not working on ATmega328p_. The code is not optimal and goes way out of the RAM's boundaries. I'll try to make it compatible once in the future.
