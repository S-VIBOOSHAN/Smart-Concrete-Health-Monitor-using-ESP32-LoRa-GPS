# Smart-Concrete-Health-Monitor-using-ESP32-LoRa-GPS
An ESP32-LoRa-GPS enabled embedded sensor capsule designed for real-time concrete curing analysis, crack detection, vibration monitoring, and long-range structural health monitoring of smart buildings, bridges, dams, and critical infrastructure.
# Smart-Concrete Health-Monitor using ESP32-GPS-ThingSpeak

## Overview

Smart-Concrete Health-Monitor is an IoT-based structural health monitoring system designed to monitor the internal condition of concrete structures in real time. The system continuously measures temperature, humidity, strain, vibration, and location data using embedded sensors and uploads the information to the ThingSpeak cloud platform for remote monitoring and analysis.

This solution helps engineers detect improper curing, crack formation, abnormal structural stress, and earthquake-induced vibrations before they become critical failures.

---

## Problem Statement

Concrete structures such as buildings, bridges, dams, tunnels, and flyovers often develop hidden defects that cannot be detected through visual inspection alone.

Common issues include:

* Improper concrete curing
* Internal crack formation
* Structural stress accumulation
* Environmental degradation
* Earthquake-induced damage

Traditional inspection methods are periodic, expensive, and unable to provide continuous monitoring.

---

## Proposed Solution

The proposed system embeds a sensor capsule inside concrete during construction.

The ESP32 collects data from:

* SHT31 Temperature & Humidity Sensor
* Strain Gauge + HX711
* MPU6050 Vibration Sensor
* NEO-6M GPS Module

Sensor data is analyzed locally and uploaded to ThingSpeak for real-time visualization and structural health assessment.

---

## Features

* Real-Time Concrete Monitoring
* Crack Detection
* Earthquake Detection
* Structural Health Score Calculation
* GPS-Based Asset Tracking
* Cloud Data Logging
* ThingSpeak Dashboard Integration
* Low-Cost IoT Architecture
* Predictive Maintenance Support

---

## Hardware Components

| Component        | Quantity    |
| ---------------- | ----------- |
| ESP32 DevKit V1  | 1           |
| SHT31 Sensor     | 1           |
| MPU6050 Module   | 1           |
| HX711 Module     | 1           |
| Strain Gauge     | 1           |
| NEO-6M GPS       | 1           |
| Breadboard / PCB | 1           |
| Jumper Wires     | As Required |
| 18650 Battery    | 1           |

---

## System Architecture

```text
SHT31
   |
MPU6050
   |
HX711 + Strain Gauge
   |
NEO-6M GPS
   |
ESP32
   |
WiFi
   |
ThingSpeak Cloud
   |
Web Dashboard
```

---

## Pin Connections

### SHT31

| SHT31 | ESP32  |
| ----- | ------ |
| VCC   | 3.3V   |
| GND   | GND    |
| SDA   | GPIO21 |
| SCL   | GPIO22 |

### MPU6050

| MPU6050 | ESP32  |
| ------- | ------ |
| VCC     | 3.3V   |
| GND     | GND    |
| SDA     | GPIO21 |
| SCL     | GPIO22 |

### HX711

| HX711 | ESP32  |
| ----- | ------ |
| DT    | GPIO32 |
| SCK   | GPIO33 |
| VCC   | 5V     |
| GND   | GND    |

### GPS

| NEO-6M | ESP32  |
| ------ | ------ |
| TX     | GPIO16 |
| RX     | GPIO17 |
| VCC    | 5V     |
| GND    | GND    |

---

## ThingSpeak Fields

| Field  | Data         |
| ------ | ------------ |
| Field1 | Temperature  |
| Field2 | Humidity     |
| Field3 | Strain       |
| Field4 | Vibration    |
| Field5 | Health Score |
| Field6 | Crack Status |
| Field7 | Latitude     |
| Field8 | Longitude    |

---

## Health Score Calculation

```cpp
Health Score = 100

Temperature > 50°C  -> -15
Humidity < 50%      -> -10
Strain > 500        -> -40
Vibration > 20000   -> -20
```

---

## Status Levels

| Score    | Condition |
| -------- | --------- |
| 90 - 100 | Excellent |
| 75 - 89  | Healthy   |
| 50 - 74  | Warning   |
| 0 - 49   | Critical  |

---

## Crack Detection Logic

```cpp
if(strainValue > 500)
{
   crackDetected = true;
}
```

---

## Earthquake Detection Logic

```cpp
if(vibrationValue > 25000)
{
   earthquakeDetected = true;
}
```

---

## Software Requirements

* Arduino IDE 2.x
* ESP32 Board Package
* ThingSpeak Account
* GitHub Account

### Required Libraries

```text
WiFi.h
HTTPClient.h
Wire.h
Adafruit_SHT31.h
TinyGPS++.h
HX711.h
MPU6050.h
```

---

## Project Workflow

```text
START
   ↓
Initialize ESP32
   ↓
Connect WiFi
   ↓
Read Sensors
   ↓
Calculate Health Score
   ↓
Detect Crack
   ↓
Detect Earthquake
   ↓
Upload to ThingSpeak
   ↓
Update Dashboard
   ↓
Repeat
```

---

## Expected Output

```text
Temperature : 29.8°C

Humidity : 76%

Strain : 120

Vibration : 14500

GPS :
13.082700
80.270700

Health Score : 96%

Crack Status : NORMAL

Earthquake Status : NORMAL

Structure Status : HEALTHY
```

---

## Applications

* Smart Buildings
* Smart Bridges
* Dams
* Metro Infrastructure
* Industrial Structures
* Smart Cities
* Infrastructure Health Monitoring

---

## Future Enhancements

* LoRa Communication
* Edge AI Prediction
* Digital Twin Integration
* Energy Harvesting
* Machine Learning Analytics
* Mobile Application
* Predictive Maintenance Engine

---

## Results

The system successfully monitors critical structural parameters and provides real-time health assessment through ThingSpeak cloud integration. Early crack detection and vibration analysis help improve infrastructure safety and reduce maintenance costs.

---

## Authors

**Vibooshan.S**
Final Year ECE Engineering Student
MUTHAYAMMAL ENGINEERING COLLAGE
Embedded Systems | IoT | Smart Infrastructure Monitoring

---

## License

This project is released under the MIT License. Feel free to use, modify, and improve the project for educational and research purposes.
