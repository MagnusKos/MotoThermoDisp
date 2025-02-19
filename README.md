# MotoThermoDisp
Just a small thing that provides an additional data about your motorbike.

## About the Project
Initially, this project designed for such motorcycles as "Minsk C4-300" and "ZiD Stayer 300-01", but it can be used on any other.
These motorbikes have the indicator of an engine overheating, but it is not in use, so as the temperature sensor.
Commercially available aftermarket indicators are too bulky ang ugly, so the author decided to make a small and a simple device,
that will be a prettier version of commercial ones. Kinda. We'll see...
The project is based on cheap arduino compatible controllers and displays.

### Built with
![PlatformIO](https://img.shields.io/badge/PlatformIO-%23222.svg?style=for-the-badge&logo=platformio&logoColor=%23f5822a)

### Project structure
- _firmware_: catalogue with platformio subproject, contains software implementation
- _model_: catalogue with FreeCad subproject, contains 3D model of the case
- _electronics_: catalogue with kicad subproject, contains schematics and pcb

## Capabilities
- [ ] Engine temperature indication
- [ ] On-board voltage indication
- [ ] Air temperature indication
- [ ] Ready-to-go state indication
- [ ] Overheating indication
- [ ] Temperature bar-graph
- [ ] Screen selectors
- [ ] Overheating output (additional LEDs, fans, locomotive air horns, etc)
