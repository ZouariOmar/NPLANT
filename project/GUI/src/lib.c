/**
 * @file lib.c
 * @author ZouariOmar (zouariomar20@gmail.com)
 * @brief The main helper file for the main project file (main.c)
 * @version 0.1
 * @date 2024-10-04
 * @copyright Copyright (c) 2024
 */

//? -------------------- INCLUDE PROTOTYPE DECLARATION PART --------------------
#include "../inc/connect.h"
#include "../inc/inc.h"

//* Init the main window
SDL_Window *window = NULL;

//* Define the main window screen resolution
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

//* SDL_COLOR PUBLIC DECLARATION
const SDL_Color WHITE = {255, 255, 255, 255};

//? ----------------------- FUNCTIONS PROTOTYPE DEV PART -----------------------

/**
 * @brief ### Init SDL2 environment
 */
void initEverything() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    exit(1);
  }

  // Initialize SDL-TTF
  if (TTF_Init() < 0) {
    printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
    exit(1);
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
  SDL_DestroyWindow(window);
  SDL_Quit();
}

/**
 * @brief ### The sub main app entry function
 */
void __lance__() {
  surface srf;
  SDL_Texture *txt = NULL;
  SDL_Surface *win = NULL;

  srf.win = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  TTF_Font *font = TTF_OpenFont("/home/zouari_omar/Documents/Daily/Projects/IoT_project/project/GUI/font/Roboto/Roboto-Black.ttf", 20);

  bool quit = false;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_KEYDOWN:
          if (e.key.keysym.sym == SDLK_f) {
            // Fetch data from Firebase
            char data[1000] = "";  // Hold the humidity value
            connectToFirebase("H1AX5Pmp8mfBOHfyAWOIjpkSBuh1", data);

            // Free existing texture if one already exists
            if (txt) {
              SDL_DestroyTexture(txt);
              txt = NULL;
            }

            // Create a new surface with the fetched data
            win = TTF_RenderText_Solid(font, data, WHITE);

            // Set surface position and dimensions
            srf.pos.x = 10;
            srf.pos.y = 10;
            srf.pos.w = win->w;
            srf.pos.h = win->h;

            // Create texture from surface before freeing it
            txt = SDL_CreateTextureFromSurface(srf.win, win);

            SDL_FreeSurface(win);  // Free surface after creating texture
            win = NULL;
          }
          break;

        case SDL_QUIT:
          quit = true;
          break;

        default:
          break;
      }
    }

    SDL_RenderClear(srf.win);  // Clear previous render

    // Render the texture if it exists
    if (txt)
      SDL_RenderCopy(srf.win, txt, NULL, &srf.pos);

    SDL_RenderPresent(srf.win);  // Show render on window
  }

  // Clean up and close
  SDL_DestroyTexture(txt);
  TTF_CloseFont(font);
  SDL_DestroyRenderer(srf.win);  // Added renderer cleanup
}