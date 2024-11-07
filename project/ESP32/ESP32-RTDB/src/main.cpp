/**
 * @file main.cpp
 * @author ZouariOmar (zouariomar20@gmail.com)
 * @brief The main ESP32 source code (lancer file)
 * @version 0.1
 * @date 2024-10-14
 * @copyright Copyright (c) 2024
 * @link https://registry.platformio.org/libraries/mobizt/Firebase%20Arduino%20Client%20Library%20for%20ESP8266%20and%20ESP32/installation PlatformIO @endlink
 * @link https://docs.platformio.org/en/latest/core/installation/udev-rules.html PlatformIO @endlink
 * ? Constraints
 * - if analogRead(SOIL_MOISTURE_PIN) > 4000 ==> Soil is too dry
 * - if analogRead(SOIL_MOISTURE_PIN) < 2000 ==> Soil is too wet
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

//* Insert our network credentials
#define WIFI_SSID "ORANGE999"                                                  // My Wi-Fi SSID @ZouariOmar
#define WIFI_PASSWORD "testtrue2002testtrue"                                   // My Wi-Fi password @ZouariOmar
#define API_KEY "AIzaSyDboLSUY1wHSCkGN6BqvZwu2k1CGMVB7Kc"                      // Insert Firebase project API Key
#define DATABASE_URL "https://iot-project-e76ac-default-rtdb.firebaseio.com/"  // Insert the RTDB URL

//* ESP32 pre-processor part
#define SOIL_MOISTURE_PIN 34

//* Define Firebase Data object
FirebaseData fb_dt;
FirebaseAuth auth;
FirebaseConfig config;

//* Declare Global vars
unsigned long sendDataPrevMillis{};
bool signupOK{};

//? Declare function part
void initWiFi();

void setup() {
  Serial.begin(115200);               // Init the ESP32 SM Frequency
  initWiFi();                         // Init the ESP32-Wifi connection
  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  // Signup part
  if (Firebase.signUp(&config, &auth, "", ""))
    Serial.println("ok"), signupOK = true;
  else
    Serial.printf("%s\n", config.signer.signupError.message.c_str());

  // Assign the callback function for the long running token generation task
  config.token_status_callback = tokenStatusCallback;  // see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    // Write the humidity data in `uid/humidity` dir
    if (Firebase.RTDB.setInt(&fb_dt, "5ziuAV9kbnSwE42E1oE3sWID1tm1/humidity", analogRead(SOIL_MOISTURE_PIN))) {
      Serial.println("PASSED!");
      Serial.println("PATH: "), Serial.print(fb_dt.dataPath());
      Serial.println("TYPE: "), Serial.print(fb_dt.dataType());
    } else
      Serial.println("FAILED"), Serial.print(fb_dt.errorReason());
  }
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