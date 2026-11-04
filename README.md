
# 🌱 AquaRoot 
Automatic Water-System for plants.

+11h of work

<img width="1902" height="1067" alt="Screenshot From 2026-11-03 21-10-52" src="https://github.com/user-attachments/assets/d6893613-78df-45aa-980f-3aadb0084651" />


# Components List

**Project:** AquaRoot  
**Version:** Rev 1.0  
**Category:** Smart Automatic Plant Watering System  
**PCB Design:** KiCad

## Screenshots
<img width="1920" height="1080" alt="Screenshot From 2026-11-01 20-24-08" src="https://github.com/user-attachments/assets/c5f01bb1-8403-4363-bb8f-732462f055da" />
<img width="866" height="521" alt="Screenshot From 2026-11-01 16-38-09" src="https://github.com/user-attachments/assets/0b5356ea-89c9-4bd2-8709-ff3ce20cda52" />
<img width="1920" height="1069" alt="Screenshot From 2026-11-01 16-59-28" src="https://github.com/user-attachments/assets/663e4c07-70a1-4047-a79a-92737e8949c5" />
<img width="1920" height="1069" alt="Screenshot From 2026-11-01 17-19-39" src="https://github.com/user-attachments/assets/32f69bc0-eb69-4e2b-b590-5c5fd07e5254" />
<img width="1920" height="1069" alt="Screenshot From 2026-11-01 17-43-35" src="https://github.com/user-attachments/assets/7f209080-defe-4839-ba56-4457a3aa6def" />
<img width="1920" height="1080" alt="Screenshot From 2026-11-01 20-24-08" src="https://github.com/user-attachments/assets/204e3949-bb5d-41be-bb9f-341514b6f155" />
<img width="793" height="813" alt="Screenshot From 2026-11-01 20-28-58" src="https://github.com/user-attachments/assets/27703b99-0b92-4f0b-81c8-ca2128f2ab20" />

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
MIT
