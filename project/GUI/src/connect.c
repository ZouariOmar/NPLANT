/**
 * @file connect.c
 * @author ZouariOmar (zouariomar20@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-10-04
 * @copyright Copyright (c) 2024
 * @link @endlink
 */

//? Include prototype declaration part
#include "../inc/connect.h"

//? ----------------------- FUNCTIONS PROTOTYPE DEV PART -----------------------
/**
 * @brief ### Helper function
 * @details Help the curl_easy_setopt() to handel the data (humidity)
 * @param contents {void *}
 * @param size {size_t }
 * @param nmemb {size_t}
 * @param userp {char *}
 * @return size_t - 0: Indicate failure | total_size: Indicate success
 */
size_t write_callback(void *contents, size_t size, size_t nmemb, char *userp) {
  size_t total_size = size * nmemb;
  char *buffer = userp;

  // Check if the buffer is large enough
  if (strlen(buffer) + total_size >= 28)
    return fprintf(stderr, "Error: Data exceeds buffer size.\n"), 0;

  // Append the data to the buffer
  strncat(buffer, contents, total_size);
  return total_size;
}

/**
 * @brief ### The main C-Firebase HTTP Get Request function
 * @param uid {char *}
 * @param data {char *}
 * @param data_size {size_t}
 * @return int - -1: Indicate error | 0: Indicate success
 */
int connectToFirebase(const char *uid, char *data, size_t data_size) {
  CURL *curl = curl_easy_init();
  CURLcode res;
  char url[2048];

  // Safely construct the full URL and handle snprintf result properly
  int ret = snprintf(url, sizeof(url), URL, uid);
  if (ret < 0 || ret >= (int)sizeof(url))
    return fprintf(stderr, "Error: URL buffer overflow or snprintf error.\n"), -1;

  if (!curl)
    return fprintf(stderr, "Error: Failed to initialize CURL.\n"), -1;

  curl_easy_setopt(curl, CURLOPT_URL, url);  // Set Firebase database URL
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);

  // Perform the GET request
  res = curl_easy_perform(curl);
  if (res != CURLE_OK)
    return fprintf(stderr, "CURL error: %s\n", curl_easy_strerror(res)), curl_easy_cleanup(curl), -1;

  // Null-terminate the data buffer
  if (data_size > 0)
    data[data_size - 1] = '\0';

  printf("HTTP 200: OK\n");
  curl_easy_cleanup(curl);
  return 0;
}