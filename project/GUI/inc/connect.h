/**
 * @file connect.h
 * @author ZouariOmar (zouariomar20@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-10-04
 * @copyright Copyright (c) 2024
 * @link https://firebase.google.com/docs/app-check/cpp/default-providers?hl=en&authuser=0 @endlink
 */

//? -------------------- DEFINE PROTOTYPE DECLARATION PART --------------------
#ifndef __CONNECT_H__
#define __CONNECT_H__
#define URL "https://iot-project-e76ac-default-rtdb.firebaseio.com/%s/humidity.json"  // Firebase URL

//? -------------------- INCLUDE PROTOTYPE DECLARATION PART --------------------
//* Stander C headers
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

//* Custom C headers


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
void connectToFirebase(char *, char *);

#endif  // __CONNECT_H__
