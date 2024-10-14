/**
 * @file main.cpp
 * @author ZouariOmar (zouariomar20@gmail.com)
 * @brief The main ESP32 source code (lancer file)
 * @version 0.1
 * @date 2024-10-14
 * @copyright Copyright (c) 2024
 * @link https://registry.platformio.org/libraries/mobizt/Firebase%20Arduino%20Client%20Library%20for%20ESP8266%20and%20ESP32/installation PlatformIO @endlink
 */

#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include <WiFi.h>

#include "../../../../../../../../../.platformio/packages/framework-arduinoespressif32/variants/nodemcu-32s/pins_arduino.h"
#include "addons/RTDBHelper.h"
#include "addons/TokenHelper.h"

// Insert our network credentials
#define WIFI_SSID "ORANGE999"
#define WIFI_PASSWORD "testtrue2002testtrue"
#define API_KEY "AIzaSyDboLSUY1wHSCkGN6BqvZwu2k1CGMVB7Kc"                      // Insert Firebase project API Key
#define DATABASE_URL "https://iot-project-e76ac-default-rtdb.firebaseio.com/"  // Insert the RTDB URL

// Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  Serial.println("Hello World!");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
