# 🌱 AquaRoot

**An automatic plant watering system powered by ESP32.**

AquaRoot is a custom-designed plant watering system that monitors soil moisture and controls a water pump to help keep plants hydrated. The project combines embedded programming, sensor interfacing, and a custom PCB designed in KiCad.

> **Project status:** PCB design completed — hardware assembly and testing are the next steps.

---

## Project Overview

| Detail | Description |
|---|---|
| Project | AquaRoot |
| Version | Rev 1.0 |
| Category | Smart Plant Care / Embedded Systems |
| Microcontroller | ESP32 DevKit V1 (ESP32-WROOM-32) |
| PCB Design Software | KiCad |
| Development Time | 11+ hours |

## Features

- Soil moisture monitoring using a capacitive analog sensor
- Automatic watering through a 5V DC pump
- Pump control using an N-channel MOSFET
- Water-level detection using a float switch
- OLED display for system information
- Manual control through push buttons
- LED indicators for power and watering status
- Buzzer for audio notifications
- Custom PCB designed in KiCad
- Expandable design for future sensors and Wi-Fi features
## Components

### Main Components

| Component | Specification | Qty | Purpose |
|---|---|---:|---|
| ESP32 DevKit V1 | ESP32-WROOM-32 | 1 | Main microcontroller |
| Soil Moisture Sensor | Capacitive, analog output | 1 | Measures soil moisture |
| DC Water Pump | 5V DC | 1 | Supplies water to the plant |
| N-Channel MOSFET | AO3400A | 1 | Switches the pump |
| Flyback Diode | SS14 / 1N5819 | 1 | Protects against inductive voltage spikes |
| Float Switch | Water-level sensor | 1 | Detects water level |

### Display & User Interface

| Component | Specification | Qty | Purpose |
|---|---|---:|---|
| OLED Display | 0.96", SSD1306, I2C | 1 | Displays system information |
| Push Buttons | Normally open, tactile | 2 | Manual user input |
| LEDs | 3mm / 5mm | 2 | Power and watering indicators |
| Buzzer | 5V | 1 | Audio notifications |

### Power Management & Protection

| Component | Specification | Qty | Purpose |
|---|---|---:|---|
| DC Power Input | 5V input connector | 1 | External power supply |
| Buck Converter | Rated for selected supply | 1 | Voltage regulation, if required |
| Fuse | Rated for pump startup current | 1 | Overcurrent protection |
| Reverse Polarity Protection | P-MOSFET or Schottky diode | 1 | Protects against reversed input |
| Power Switch | SPST | 1 | Main power control |
| Capacitors | 100nF | 3 | High-frequency decoupling |
| Capacitors | 10µF | 2 | Power stabilization |
| Capacitor | 470µF | 1 | Pump supply buffering |

### Passive Components

| Component | Value | Qty | Purpose |
|---|---|---:|---|
| Resistor | 100Ω | 1 | MOSFET gate resistor |
| Resistor | 100kΩ | 1 | MOSFET gate pull-down |
| Resistor | 220Ω | 2 | LED current limiting |
| Resistor | 10kΩ | 2 | Pull-up / pull-down |
| Resistor | 1kΩ | 1 | General-purpose current limiting |

### Connectors & PCB

| Component | Specification | Qty | Purpose |
|---|---|---:|---|
| Screw Terminals | 2-pin | 2 | Pump and power connections |
| JST Connector | 3-pin | 1 | Soil moisture sensor |
| JST Connector | 2-pin | 1 | Water-level sensor |
| Pin Headers | 2.54mm | 1 set | ESP32 connection |
| Custom PCB | Designed in KiCad | 1 | Main circuit board |

## 🔌 System Design

AquaRoot is built around an ESP32 microcontroller.

The soil moisture sensor provides an analog measurement to the ESP32. Based on the programmed moisture threshold, the ESP32 controls the water pump through an N-channel MOSFET. A float switch provides water-level detection, while the OLED, buttons, LEDs, and buzzer provide user interaction and system feedback.

The PCB includes power input, switching, connectors, and supporting components for the system.

## 🛠️ PCB Design

The AquaRoot PCB was designed using **KiCad**.

Design work includes:
- Schematic capture
- Component selection and footprint assignment
- PCB layout
- Track routing
- Design Rule Check (DRC)
- Gerber and drill file generation

**PCB dimensions:** 92 mm × 63 mm

## 📷 Design Screenshots

### Schematic

![AquaRoot Schematic](https://github.com/user-attachments/assets/c5f01bb1-8403-4363-bb8f-732462f055da)

### PCB Layout

![AquaRoot PCB Layout](https://github.com/user-attachments/assets/0b5356ea-89c9-4bd2-8709-ff3ce20cda52)

![AquaRoot PCB Routing](https://github.com/user-attachments/assets/663e4c07-70a1-4047-a79a-92737e8949c5)

![AquaRoot PCB Design](https://github.com/user-attachments/assets/32f69bc0-eb69-4eb2-b590-5c5fd07e5254)

![AquaRoot PCB View](https://github.com/user-attachments/assets/7f209080-defe-4839-ba56-4457a3aa6def)

![AquaRoot PCB Final View](https://github.com/user-attachments/assets/204e3949-bb5d-41be-bb9f-341514b6f155)

### Additional Design View

![AquaRoot Design](https://github.com/user-attachments/assets/27703b99-0b92-4f0b-81c8-ca2128f2ab20)

## Future Improvements

Potential upgrades for future revisions:

| Upgrade | Purpose |
|---|---|
| DS3231 RTC | Scheduled watering |
| BH1750 | Light intensity monitoring |
| DHT22 | Temperature and humidity monitoring |
| Second Moisture Sensor | Monitor another plant |
| Wi-Fi Dashboard | Remote monitoring and control |
| Data Logging | Track moisture readings and watering history |

## Planned Development

- [x] Design the circuit schematic
- [x] Design the custom PCB
- [x] Route PCB tracks
- [x] Run PCB design checks
- [x] Generate manufacturing files
- [ ] Manufacture the PCB
- [ ] Assemble the components
- [ ] Develop and upload ESP32 firmware
- [ ] Test soil moisture readings
- [ ] Test automatic pump control
- [ ] Validate the complete system

# Last Updates
- Replaced push buttons with 2 pins (New-Footprint: Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical Old-Footprint: Button_Switch_THT:SW_PUSH_6mm )
- Replaced leds with 2 pins (New-Footprint: Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical Old-Footprint: LED_THT:LED_D5.0mm)
## Author

**Deadcode**

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
