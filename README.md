# IoT-Based Satellite Health Monitoring System 

Link to project - https://wokwi.com/projects/436207917236812801


This project simulates a real-time satellite health monitoring system using an **ESP32** and **Firebase Realtime Database** — entirely developed in the **Wokwi online simulator**. It mimics how satellites monitor internal conditions like temperature and battery voltage, sending alerts and status data wirelessly to ground stations.

---

## 📸 Project Preview

> 

https://github.com/user-attachments/assets/20eee430-b703-4062-a517-6371f627b756



with arduino -



https://github.com/user-attachments/assets/8ee2f2c2-4094-40c5-a447-d4f5ffbb4a92



---

## 🔧 Hardware Simulation

| Component              | Description                                     |
|------------------------|-------------------------------------------------|
| **ESP32 DevKit V1**     | Main microcontroller with Wi-Fi capabilities   |
| **2x Potentiometers**   | Simulate sensors for temperature and voltage   |
| **SSD1306 OLED Display**| Display telemetry in real-time                 |
| **Red, Green, Blue LEDs** | Indicate satellite health status               |
| **Buzzer**              | Audio alert for system faults                  |
| **Firebase**            | Cloud database to store & sync live data       |

---

## 💡 Features

- 🔥 **Temperature Simulation** using potentiometer (0–50°C)
- 🔋 **Voltage Simulation** using potentiometer (0–5V)
- 📟 Live **telemetry display** on OLED
- 🟢🟡🔴 RGB LED indicates:
  - **Green** → Normal  
  - **Red** → Overheat  
  - **Blue** → Low battery
- 🔊 **Buzzer alerts** on abnormal conditions
- ☁️ **Firebase sync**: Real-time data sent to the cloud

---

## 🔌 Circuit Connections

### 📍 Potentiometers

| Pin     | Connection         |
|---------|--------------------|
| VCC     | `3.3V` on ESP32     |
| GND     | `GND` on ESP32      |
| SIG Pot 1 (Temp) | `GPIO39 (VN)` |
| SIG Pot 2 (Volt) | `GPIO36 (VP)` |

### 📍 OLED Display

| Pin | ESP32 Pin |
|-----|-----------|
| VCC | `3.3V`    |
| GND | `GND`     |
| SDA | `GPIO21`  |
| SCL | `GPIO22`  |

### 📍 LEDs & Buzzer

| Device | Pin | ESP32 GPIO |
|--------|-----|-------------|
| Red LED    | A | `GPIO18` |
| Green LED  | A | `GPIO19` |
| Blue LED   | A | `GPIO23` |
| All LED C  | C | `GND`    |
| Buzzer +   | 1 | `GPIO5`  |
| Buzzer −   | 2 | `GND`    |

---

## ☁️ Firebase Setup

1. Go to [Firebase Console](https://console.firebase.google.com/)  
2. Create a Realtime Database  
3. Set Rules for testing:
```json
{
  "rules": {
    ".read": true,
    ".write": true
  }
}
