/**
 * @file connect.h
 * @author ZouariOmar (zouariomar20@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-10-04
 * @copyright Copyright (c) 2024
 */

//? -------------------- DEFINE PROTOTYPE DECLARATION PART --------------------
#ifndef __CONNECT_H__
#define __CONNECT_H__
#define URL "https://iot-project-e76ac-default-rtdb.firebaseio.com/humidity.json"  // Firebase URL (adjust with your own database URL and data path)

/**
 * TODO: Need auth token to secure our DB (auth.uid, custom password, Enforced check app - reCAPTCHA -) `#define AUTH_TOKEN ""`
 * @link https://firebase.google.com/docs/app-check/cpp/default-providers?hl=en&authuser=0 @endlink
 */

//? -------------------- INCLUDE PROTOTYPE DECLARATION PART --------------------
//* STANDARD LIBS INCLUDE PART
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

//? --------------------- PUBLIC VARS DECLARATION PART ---------------------
/*
None...
*/

//? Structures prototype declaration part
/*
None...
*/

//? Functions prototype declaration part
size_t write_callback(void *, size_t, size_t, char *);
void connectToFirebase();

#endif  // __CONNECT_H__
