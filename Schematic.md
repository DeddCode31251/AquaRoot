# 📐 Schematic & Design

AquaRoot's electronic circuit is designed using **KiCad**. The schematic is organized into functional sections to make the hardware easier to understand, develop, test, and maintain.

## 1. System Architecture

The system is built around an ESP32 microcontroller that monitors soil moisture and controls an automatic irrigation mechanism.

## 2. Schematic Sections

The schematic is divided into the following functional blocks:

| Section | Components | Description |
|---|---|---|
| Power Management | Power connector, capacitors, protection | Provides stable and protected power |
| Main Controller | ESP32 DevKit | Processes sensor readings and controls the system |
| Soil Monitoring | Capacitive soil moisture sensor | Measures soil moisture |
| Water Level Detection | Float switch | Detects low water levels |
| Pump Driver | N-channel MOSFET, flyback diode | Controls the DC water pump |
| Display | SSD1306 OLED | Displays system information |
| User Interface | Push buttons | Provides manual control |
| Indicators | LEDs, resistors | Displays system status |

## 3. GPIO Pin Configuration

Initial proposed ESP32 pin assignment:

| ESP32 GPIO | Component | Function |
|---|---|---|
| GPIO34 | Soil Moisture Sensor | Analog input |
| GPIO25 | MOSFET Driver | Pump control |
| GPIO27 | Float Switch | Water level detection |
| GPIO21 | OLED SDA | I2C data |
| GPIO22 | OLED SCL | I2C clock |
| GPIO32 | Push Button 1 | Manual watering |
| GPIO33 | Push Button 2 | Settings |
| GPIO2 | Status LED | Power indicator |
| GPIO4 | Status LED | Pump indicator |

*Note: GPIO assignments are preliminary and will be verified against the selected ESP32 board and final circuit.*

## 4. Pump Driver Circuit

AquaRoot uses an N-channel logic-level MOSFET to control the DC water pump.

Main components:

- AO3400A N-channel MOSFET.
- SS14 / 1N5819 flyback diode.
- 100Ω gate resistor.
- 100kΩ gate pull-down resistor.
- DC water pump.

The ESP32 controls the MOSFET through a GPIO output. This allows the pump to operate without drawing its current directly from the microcontroller.

## 5. Power Management

The initial design targets a 5V DC power input.

Power management includes:

- Input power connector.
- Power switch.
- Overcurrent protection.
- Reverse polarity protection.
- Voltage regulation for the ESP32.
- Decoupling and bulk capacitors.

The pump power branch will be sized independently according to the pump's operating and startup current.

## 6. Design Software

| Software | Purpose |
|---|---|
| KiCad | Schematic and PCB design |
| Arduino IDE | ESP32 firmware development |
| C++ | Embedded programming |

## 7. Design Workflow

1. Create the electrical schematic.
2. Select and verify electronic components.
3. Assign KiCad symbols.
4. Assign component footprints.
5. Run Electrical Rules Check (ERC).
6. Design PCB layout.
7. Run Design Rules Check (DRC).
8. Generate Gerber and drill files.
9. Assemble and test the PCB.

## 8. Current Design Status

| Task | Status |
|---|---|
| Project architecture | Planned |
| Component selection | Initial selection |
| Power circuit | Pending |
| ESP32 connections | Pending |
| Sensor circuits | Pending |
| Pump driver | Pending |
| OLED interface | Pending |
| Complete schematic | Pending |
| PCB layout | Pending |
| Hardware testing | Pending |

---

**Design Goal:** Develop a reliable, modular, and expandable automatic plant watering system using ESP32 and custom-designed PCB hardware.
