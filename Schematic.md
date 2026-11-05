# Schematic & Design

AquaRoot's electronic circuit is designed using **KiCad**. The schematic is organized into functional sections to make the hardware easier to understand, develop, test, and maintain.

## 1. System Architecture

AquaRoot is built around an ESP32 DevKit V1 (ESP32-WROOM-32). It monitors soil moisture and controls a 5V DC water pump through an N-channel MOSFET.

A float switch monitors the water level. An OLED display, push buttons, LEDs, and a buzzer provide system feedback and user interaction.

The design uses a custom PCB measuring **92 mm × 63 mm**.

## 2. Schematic Sections

| Section | Components | Description |
|---|---|---|
| Power Input | 5V connector, fuse, power switch | Supplies the system |
| Power Filtering | 470µF and 100nF capacitors | Helps stabilize the supply |
| Main Controller | ESP32 DevKit V1 | Processes sensor readings and controls outputs |
| Soil Monitoring | Capacitive moisture sensor | Measures soil moisture |
| Water Level Detection | Float switch | Detects water level |
| Pump Driver | N-channel MOSFET, flyback diode, resistors | Switches the DC water pump |
| Display | SSD1306 OLED | Displays system information |
| User Interface | Two push buttons | Provides manual input |
| Indicators | LEDs and current-limiting resistors | Indicates system status |
| Audio Feedback | 5V buzzer | Provides notifications |

## 3. GPIO Pin Configuration

The following pin assignments reflect the current schematic design.

| ESP32 GPIO | Component | Function |
|---|---|---|
| GPIO34 | Soil Moisture Sensor | Analog sensor input |
| GPIO25 | MOSFET Gate | Pump control |
| GPIO27 | Float Switch | Water-level detection |
| GPIO21 | OLED SDA | I2C data |
| GPIO22 | OLED SCL | I2C clock |
| GPIO32 | MODE Button | User input |
| GPIO33 | SELECT Button | User input |
| GPIO18 | Pump Indicator LED | Watering status |
| GPIO4 | Buzzer | Audio notifications |

**Power indicator:** The power LED is connected to the 3.3V supply through a current-limiting resistor.

*Note: These assignments describe the schematic. Firmware
