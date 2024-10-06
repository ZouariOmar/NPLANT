/**
 * @file main.c
 * @author ZouariOmar (zouariomar20@gmail.com)
 * @brief The main c src file
 * @version 0.1
 * @date 2024-10-04
 * @copyright Copyright (c) 2024
 */

//? ------------------------------ INCLUDE PROTOTYPE DECLARATION PART ------------------------------
#include "../inc/connect.h"
#include "../inc/inc.h"

//? --------------------------------- MAIN() INT FUNCTION DEV PART ---------------------------------

/**
 * @brief # The Main program function
 * @return int
 */
int main() {
  initEverything();

  // Create renderer
  surface srf;
  srf.win = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Present the rendered image
  SDL_RenderPresent(srf.win);

  bool running = true;
  SDL_Event e;

  while (running) {
    SDL_SetRenderDrawColor(srf.win, 0, 0, 255, 1);
    SDL_RenderClear(srf.win);
    SDL_RenderPresent(srf.win);

    SDL_Delay(2000);

    SDL_SetRenderDrawColor(srf.win, 0, 255, 0, 1);
    SDL_RenderClear(srf.win);
    SDL_RenderPresent(srf.win);

    SDL_Delay(2000);

    SDL_SetRenderDrawColor(srf.win, 255, 0, 0, 1);
    SDL_RenderClear(srf.win);
    SDL_RenderPresent(srf.win);

    SDL_Delay(2000);

    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_QUIT:  // Exit the app
          running = false;
          break;
        case SDL_KEYDOWN:
          if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)  // Exit the app
            running = false;
          break;
        default:
          break;
      }
    }
  }

  // Set render color (background color)
  SDL_SetRenderDrawColor(srf.win, 255, 255, 255, 255);  // White
  SDL_RenderClear(srf.win);
  SDL_RenderPresent(srf.win);

  char data[1000] = "";  // Hold the humidity value (!for now we hold all the usr data)
  connectToFirebase("H1AX5Pmp8mfBOHfyAWOIjpkSBuh1", data);
  printf("Your plant humidity: %s", data);

  // Clean up and close
  SDL_DestroyRenderer(srf.win);
  closeEverything();

  return 0;
}
