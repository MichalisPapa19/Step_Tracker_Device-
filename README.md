# 👟 Foot-Wearable Step Counter

This project presents the design and implementation of a **foot-wearable step detection device**, developed as part of a diploma thesis at the International Hellenic University.


## 📖 Overview

The goal of this project is to develop a wearable system capable of accurately detecting user steps by placing the device on the **foot**, improving accuracy compared to wrist-based devices.

The system combines:
- Embedded hardware (microcontroller + sensors)
- Firmware for data acquisition
- Python-based algorithms for step detection


## ⚙️ Hardware Components

- **PIC18F57Q43 Microcontroller**  
  Main processing unit of the system.

- **BNO055 Sensor (9-DOF IMU)**  
  Provides acceleration, gyroscope, and orientation data.

- **OLED Display (SSD1306 128x64)**  
  Displays real-time sensor measurements.

- **CP2102 USB-to-Serial Converter**  
  Enables communication with a computer.

## 🔌 System Architecture

- Sensor data collected via **I2C**
- Processed by the microcontroller
- Displayed on **OLED screen**
- Transmitted via **UART (CP2102)**

## 💻 Software

### Embedded Firmware
- Language: **C**
- Features:
  - I2C communication with sensor
  - OLED control
  - UART data transmission

### Data Processing
- Language: **Python**
- Implements:
  - Step detection algorithm
  - Distance estimation

## 🧠 Step Detection Algorithm

The algorithm includes:
- Signal preprocessing
- Peak detection
- Noise filtering

## 🧪 Experimental Setup

- Device mounted on the **foot**
- Powered via **power bank**
- Real-time display using OLED
- Data logging via serial connection

## 🧱 Mechanical Design

- Designed in **FreeCAD**
- 3D printed using **PLA**
- Mounted using **Velcro straps**


## 🎓 Author
Michail Papaioannou
Department of Informatics, Computer and Telecommunications Engineering
International Hellenic University

**📅 Year 
   2025
