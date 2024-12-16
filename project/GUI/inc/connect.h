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
#define URL ".env"  // Firebase URL
#define JSON_DATA_POST_REQUEST ".env"
#define GOOGLE_API ".env"  // Firebase URL + ProjectApiKey

//? -------------------- INCLUDE PROTOTYPE DECLARATION PART --------------------
//* Stander C headers
#include <cjson/cJSON.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//? Functions prototype declaration part
size_t write_callback(void *, size_t, size_t, char *);
int connectToFirebase(const char *, char *, size_t);

#endif  // __CONNECT_H__
