# 🌱 AquaRoot 
Automatic Water-System for plants.

# Components List

**Project:** AquaRoot  
**Version:** Rev 1.0  
**Category:** Smart Automatic Plant Watering System  
**PCB Design:** KiCad

## 1. Main Components

| Component | Specification | Quantity | Purpose |
|---|---|---:|---|
| ESP32 DevKit V1 | ESP32-WROOM-32 | 1 | Main microcontroller |
| Soil Moisture Sensor | Capacitive, analog output | 1 | Measures soil moisture |
| DC Water Pump | 5V DC | 1 | Waters the plant |
| N-Channel MOSFET | AO3400A | 1 | Controls the water pump |
| Flyback Diode | SS14 / 1N5819 | 1 | Protects against inductive voltage spikes |
| Water Level Sensor | Float switch | 1 | Detects low water level |

## 2. Display & User Interface

| Component | Specification | Quantity | Purpose |
|---|---|---:|---|
| OLED Display | 0.96", SSD1306, I2C | 1 | Displays system information |
| Push Button | Tactile, normally open | 2 | Manual control |
| LED | 3mm / 5mm | 2 | Power and watering indicators |
| Buzzer | 5V | 1 | Audio notifications |

## 3. Power Management & Protection

| Component | Specification | Quantity | Purpose |
|---|---|---:|---|
| DC Power Input | 5V input connector | 1 | External power |
| Buck Converter | Input/output rated for selected supply | 1 | Voltage regulation if required |
| Fuse | Rated for pump startup current | 1 | Overcurrent protection |
| Reverse Polarity Protection | P-MOSFET or Schottky diode | 1 | Input protection |
| Power Switch | SPST | 1 | Main power control |
| Capacitor | 100nF | 3 | High-frequency decoupling |
| Capacitor | 10µF | 2 | Power stabilization |
| Capacitor | 470µF | 1 | Pump supply buffering |

## 4. Passive Components

| Component | Value | Quantity | Purpose |
|---|---|---:|---|
| Resistor | 100Ω | 1 | MOSFET gate resistor |
| Resistor | 100kΩ | 1 | MOSFET gate pull-down |
| Resistor | 220Ω | 2 | LED current limiting |
| Resistor | 10kΩ | 2 | Pull-up / pull-down |
| Resistor | 1kΩ | 1 | General-purpose current limiting |

## 5. Connectors & PCB Components

| Component | Specification | Quantity | Purpose |
|---|---|---:|---|
| Screw Terminal | 2-pin | 2 | Pump and power connections |
| JST Connector | 3-pin | 1 | Soil moisture sensor |
| JST Connector | 2-pin | 1 | Water level sensor |
| Pin Header | 2.54mm | 1 set | ESP32 connection |
| PCB | Custom-designed | 1 | Main circuit board |

## 6. Future Upgrades

| Component | Specification | Purpose |
|---|---|---|
| DS3231 RTC | Real-time clock | Scheduled watering |
| BH1750 | Light intensity sensor | Monitor sunlight |
| DHT22 | Temperature and humidity | Environmental monitoring |
| Second Moisture Sensor | Capacitive analog | Monitor another plant |
| Wi-Fi Dashboard | ESP32 Wi-Fi | Remote monitoring and control |

---


# Author 
Deadcode

# License
