/**
 * @file connect.c
 * @author ZouariOmar (zouariomar20@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-10-04
 * @copyright Copyright (c) 2024
 */

//? Include prototype declaration part
#include "../inc/connect.h"

/**
 * @brief ### Helper function
 * @details Help the curl_easy_setopt() to handel the data (humidity)
 * @param ptr {void *}
 * @param size {size_t}
 * @param nmemb {size_t}
 * @param data {data *}
 * @return size_t
 */
size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data) {
  strncat(data, (char *)ptr, size * nmemb);
  return size * nmemb;
}

/**
 * @brief ### The main C-Firebase HTTP Get Request function
 */
void connectToFirebase() {
  CURL *curl = curl_easy_init();
  CURLcode res;
  char data[10000] = "";  // Buffer to store response data (or = {0})

  curl_global_init(CURL_GLOBAL_DEFAULT);

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, URL);  // Set Firebase database URL

    // Specify the write callback function to handle the data
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);

    // Perform the GET request
    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    else
      printf("Humidity: %s\n", data);

    // Cleanup the curl var
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();
}
