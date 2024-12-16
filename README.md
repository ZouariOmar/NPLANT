<!-- PROJECT SHIELDS -->

[![Contributors](https://img.shields.io/badge/CONTRIBUTORS-02-blue?style=plastic)](https://github.com/ZouariOmar/NPLANT/graphs/contributors) [![Forks](https://img.shields.io/badge/FORKS-00-blue?style=plastic)](https://github.com/ZouariOmar/NPLANT/network/members)
[![Stargazers](https://img.shields.io/badge/STARS-02-blue?style=plastic)](https://github.com/ZouariOmar/NPLANT/stargazers)
[![Issues](https://img.shields.io/badge/ISSUES-00-blue?style=plastic)](https://github.com/ZouariOmar/NPLANT/issues)
[![MIT License](https://img.shields.io/badge/LICENSE-MIT_Non_Commercial_License_with_Exclusive_Commercial_Rights-blue?style=plastic)](LICENSE)
[![LinkedIn](https://img.shields.io/badge/-LinkedIn-black.svg?style=plastic&logo=linkedin&colorB=blue)](https://www.linkedin.com/in/zouari-omar-143239283)

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/ZouariOmar/NPLANT">
    <img src="doc/imgs/logo.png" alt="Logo" width="400" height="400">
  </a>

<h3 align="center">NPLANT</h3>

  <p align="center">
    Desktop app to present the NPLANT project
    <br />
    <a href="https://github.com/ZouariOmar/NPLANT"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/ZouariOmar/NPLANT">View Demo</a>
    ·
    <a href="https://github.com/ZouariOmar/NPLANT/issues/new?labels=bug&template=bug-report---.md">Report Bug</a>
    ·
    <a href="https://github.com/ZouariOmar/NPLANT/issues/new?labels=enhancement&template=feature-request---.md">Request Feature</a>
  </p>
</div>

# IoT Plant Humidity Detector

This project is a simple IoT solution to help plant owners monitor the humidity levels of their plants. The system uses an ESP32 to detect the humidity level of the soil. When the humidity falls below a predefined threshold, a notification/alert is sent to the plant owner via Firebase. The owner can also monitor the humidity level through a GUI application developed in C.

## Features

- **Humidity Detection**: Continuously monitors the soil moisture level using a humidity sensor.
- **Real-time Notifications**: Sends alerts via Firebase when the moisture level is too low.
- **User-Friendly GUI**: A C-based desktop application that provides real-time data visualization of the plant’s humidity levels.
- **WiFi Connectivity**: The ESP32 communicates with Firebase using WiFi.

## Components

- **ESP32**: The microcontroller that reads humidity data from the sensor and communicates with Firebase.
- **Humidity Sensor**: Detects the moisture level in the soil.
- **Firebase**: Acts as a real-time database and notification system.
- **GUI App**: A C language-based desktop app for monitoring humidity in real-time.

## Hardware Requirements

- ESP32
- Soil moisture sensor
- USB cable for ESP32 connection
- WiFi-enabled environment
- Power source for the ESP32

## Software Requirements

- **Arduino IDE or PlatformIO**: To program the ESP32.
- **Firebase Account**: To set up the real-time database and notification system.
- **C Compiler (GCC/MinGW)**: For compiling the desktop application.
- **SDL2**: For GUI rendering in the C app.
- **Firebase Library for ESP32**: Allows the ESP32 to interact with Firebase.

## System Architecture

1. **ESP32 and Sensor**: The ESP32 reads soil moisture levels using the connected sensor.
2. **Firebase Integration**: The ESP32 sends the moisture data to Firebase in real-time. If the moisture level falls below a set threshold, Firebase triggers a notification alert.
3. **GUI App**: The desktop application connects to Firebase, visualizes the current humidity levels, and displays alerts when the plant needs watering.

## How it Works

1. **Setup**: Place the soil moisture sensor into the plant's soil and connect it to the ESP32.
2. **Monitoring**: The ESP32 reads the humidity level every few minutes and uploads the data to Firebase.
3. **Alert**: If the moisture level drops below the predefined threshold, an alert is sent to the plant owner via Firebase Cloud Messaging.
4. **User Interface**: The desktop app provides a real-time display of the plant's humidity level and sends pop-up notifications when it is time to water the plant.

## Setup Guide

### ESP32 Setup

1. **Install Libraries**: Install the necessary libraries for Firebase and the moisture sensor:

   - [Firebase ESP32 Library](https://github.com/mobizt/Firebase-ESP32)
   - Adafruit Soil Moisture Sensor Library

2. **Configure Firebase**: Set up a Firebase project and obtain your Firebase credentials (`projectID`, `databaseURL`, etc.).

3. **ESP32 Code**: Flash the following code to your ESP32 to collect sensor data and send it to Firebase.

```cpp
#include <FirebaseESP32.h>
#include <WiFi.h>

// Firebase credentials
#define FIREBASE_HOST "your_firebase_url"
#define FIREBASE_AUTH "your_firebase_auth_key"

// WiFi credentials
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";

// Pin where the soil moisture sensor is connected
#define SENSOR_PIN 34

// Firebase object
FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  int moistureLevel = analogRead(SENSOR_PIN);

  // Upload data to Firebase
  Firebase.setInt(firebaseData, "/plant/humidity", moistureLevel);

  // Check if the moisture level is below the threshold
  if (moistureLevel < 300) {
    Firebase.setString(firebaseData, "/plant/alert", "Water your plant!");
  } else {
    Firebase.setString(firebaseData, "/plant/alert", "");
  }

  delay(60000); // Read sensor data every 1 minute
}
```

## acknowledge

- UID: [Unique Identification Number](https://en.wikipedia.org/wiki/Unique_identifier)

- FRTDB: [Firebase Realtime Database](https://firebase.google.com/docs/database)
