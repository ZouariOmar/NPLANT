/**
 * @file lib.c
 * @author ZouariOmar (zouariomar20@gmail.com)
 * @brief The main helper file for the main project file (main.c)
 * @version 0.1
 * @date 2024-10-04
 * @copyright Copyright (c) 2024
 */

//? -------------------- INCLUDE PROTOTYPE DECLARATION PART --------------------
#include "../inc/inc.h"

//* Init the main window
SDL_Window *window = NULL;

//* Define the main window screen resolution
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

//? ----------------------- FUNCTIONS PROTOTYPE DEV PART -----------------------

/**
 * @brief ### Init SDL2 environment
 */
void initEverything() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
  }

  // Create window
  window = SDL_CreateWindow(PROJECT_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
  }
}

/**
 * @brief ### Close SDL2 resources in exit action
 */
void closeEverything() {
  // Mix_CloseAudio();
  // IMG_Quit();
  // TTF_Quit();
  SDL_Quit();
  SDL_DestroyWindow(window);
}

/**
 * @brief ### Set the screen window mode
 * *
 * - x(0) - The screen will be in Windowed Mode
 * *
 * - x(SDL_WINDOW_FULLSCREEN) - The screen will be in Fullscreen Mode
 * @param x {int}
 */
inline void setScreen(int x) {
  (!x) ? SDL_SetWindowFullscreen(window, 0) : SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}

/**
 * @brief ### Free All Resources (range 0 to numberOfResources - 1)
 * @param sub {surface *}
 * @param nb_res {int}
 */
void freeResources(surface *sub, int nb_res) {
  for (int i = 0; i < nb_res; i++)
    SDL_DestroyRenderer(sub[i].win);
}