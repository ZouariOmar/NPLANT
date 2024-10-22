/**
 * @file main.cpp
 * @author ZouariOmar (zouariomar20@gmail.com)
 * @brief The main ESP32 source code (lancer file)
 * @version 0.1
 * @date 2024-10-14
 * @copyright Copyright (c) 2024
 * @link https://registry.platformio.org/libraries/mobizt/Firebase%20Arduino%20Client%20Library%20for%20ESP8266%20and%20ESP32/installation PlatformIO @endlink
 * @link https://docs.platformio.org/en/latest/core/installation/udev-rules.html PlatformIO @endlink
 */

//? Include std C++ libs
#include <iostream>

//? Include std ESP32 libs (support c++)
#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include <WiFi.h>

//? Include .pio lib_deps
#include "../../../../../../../../../.platformio/packages/framework-arduinoespressif32/variants/nodemcu-32s/pins_arduino.h"
#include "addons/RTDBHelper.h"
#include "addons/TokenHelper.h"

// Insert our network credentials
#define WIFI_SSID "ORANGE999"
#define WIFI_PASSWORD "testtrue2002testtrue"
#define API_KEY "AIzaSyDboLSUY1wHSCkGN6BqvZwu2k1CGMVB7Kc"                      // Insert Firebase project API Key
#define DATABASE_URL "https://iot-project-e76ac-default-rtdb.firebaseio.com/"  // Insert the RTDB URL

// Define Firebase Data object
FirebaseData fb_dt;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * @brief ### Connect the ESP32 board with the wifi
 * *
 * - #### Dependencies: WIFI_SSID && WIFI_PASSWORD
 */
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');  // @test Count how many time the ESP32 failed to connect
    delay(1000);        // or delay(300); ==> more fast with hight crash rate
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.print(WiFi.localIP());  // Get ESP32 IP Address
  Serial.println();
}

void loop() {
  Serial.begin(115200);  // Init the ESP32 SM Frequency
  initWiFi();            // Init the ESP32-Wifi connection
}
