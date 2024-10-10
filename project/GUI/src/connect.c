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
  size_t realsize = size * nmemb;

  // Ensure we don't overflow the data buffer
  strncat(data, (char *)ptr, realsize);

  return realsize;
}

/**
 * @brief ### The main C-Firebase HTTP Get Request function
 */
void connectToFirebase(char *uid, char *data) {
  CURL *curl = curl_easy_init();
  CURLcode res;
  char url[2048];
  sprintf(url, URL, uid);  // Full url format (RTDB + uid)

  curl_global_init(CURL_GLOBAL_DEFAULT);

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);  // Set Firebase database URL

    // Specify the write callback function to handle the data (@YoussefSaaidi2004 ya 7alawa)
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);

    // Perform the GET request
    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    else
      printf("%s", "HTTP 200: OK\n");

    // Cleanup the curl var
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();
}

//////////////////////////////////////////////////////////////////////

/**
 * @brief ### Sign in to the firebase Auth account using email and password
 * @details We are using the POST HTTP REQUEST METHOD
 * ! Not stable (Testing mode)
 * @bug {double free or corruption (!prev) \n./run.sh: line 11: 99686 Aborted (core dumped) ./app}
 * @param email {const char *}
 * @param password {const char *}
 */
void firebase_sign_in(const char *email, const char *password) {
  CURL *curl;
  CURLcode res;

  // Allocate memory for the response string
  char *response = (char *)malloc(1000 * sizeof(char));
  if (!response) {
    fprintf(stderr, "Failed to allocate memory for response\n");
    return;
  }
  response[0] = '\0';  // Initialize response string

  curl = curl_easy_init();
  if (curl) {
    // Firebase Sign-In URL with API key
    const char *url = "https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=AIzaSyDboLSUY1wHSCkGN6BqvZwu2k1CGMVB7Kc";

    // Prepare the JSON data for the POST request
    char post_data[256];
    sprintf(post_data, JSON_DATA_POST_REQUEST, email, password);

    /**
     * ! Testing part
     * * Passed!
     * ? Tested in Postman
     */
    printf("Post data: %s\n", post_data);

    // Set cURL options for POST request
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, (struct curl_slist *)curl_slist_append(NULL, "Content-Type: application/json"));  // Set Content-Type to application/json
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);                                                                                 // Enable verbose output  //! Testing mode

    // Perform the request
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "cURL failed: %s\n", curl_easy_strerror(res));
    }

    // Clean up
    curl_easy_cleanup(curl);
  }

  printf("Response: %s\n", response);
  free(response);  // Free the response buffer
  response = NULL;
  curl_global_cleanup();
}