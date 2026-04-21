**👟 Foot-Wearable Step Counter

This project presents the design and implementation of a foot-wearable step detection device, developed as part of a diploma thesis at the International Hellenic University.

📖 Overview

The goal of this project is to develop a wearable system capable of accurately detecting user steps by placing the device on the foot, improving accuracy compared to wrist-based devices.

The system combines:

*Embedded hardware (microcontroller + sensors)
*Firmware for data acquisition
*Python-based algorithms for step detection

**⚙️ Hardware Components

The device consists of the following main components:

*PIC18F57Q43 Microcontroller
Acts as the main processing unit of the system.
*BNO055 Sensor (9-DOF IMU)
Provides acceleration, gyroscope, and orientation data.
*OLED Display (SSD1306 128x64)
Displays real-time sensor measurements.
*CP2102 USB-to-Serial Converter
Enables communication between the device and a computer.

**🔌 System Architecture
 *Sensor data is collected via I2C communication
 *Data is processed by the microcontroller
 *Measurements are displayed on the OLED screen
 *Data is transmitted to a PC via UART (CP2102)

**💻 Software
**Embedded Firmware
*Developed in C
*Handles:
  *Sensor communication (I2C)
  *Display control (OLED)
  *Serial communication (UART)
  *Data Processing
  *Implemented in Python
  *Uses heuristic algorithms for:
  *Step detection
  *Distance estimation

**🧠 Step Detection Algorithm

The step detection is based on:
*Preprocessing of accelerometer data
*Peak detection
*Filtering techniques to remove noise

**🧪 Experimental Setup
*The device is mounted on the user's foot
*Powered via power bank
*Real-time data monitoring via OLED display
*Data logging through serial communication

**🧱 Mechanical Design
*Custom enclosure designed in FreeCAD
*3D printed using PLA material
*Adjustable mounting using Velcro straps


**📊 Results

The system demonstrates:

*Reliable step detection
*Improved accuracy due to foot placement
*Real-time monitoring capability

**🎓 Author
Michail Papaioannou
Department of Informatics, Computer and Telecommunications Engineering
International Hellenic University

**📅 Year 
   2025
