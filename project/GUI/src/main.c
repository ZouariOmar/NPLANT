/**
 * @file main.c
 * @author ZouariOmar (zouariomar20@gmail.com)
 * @brief The main c src file
 * @version 0.1
 * @date 2024-10-04
 * @copyright Copyright (c) 2024
 */

//? ------------------------------ INCLUDE PROTOTYPE DECLARATION PART ------------------------------
#include "../inc/inc.h"
#include "../inc/connect.h"

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
  if (!srf.win) {
    fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  // Set render color (background color)
  SDL_SetRenderDrawColor(srf.win, 255, 255, 255, 255);  // White
  SDL_RenderClear(srf.win);

  // Set color for the rectangle
  SDL_SetRenderDrawColor(srf.win, 0, 0, 255, 255);  // Blue

  // Create a rectangle

  srf.pos.x = (SCREEN_WIDTH - 200) / 2;   // Centered
  srf.pos.y = (SCREEN_HEIGHT - 100) / 2;  // Centered
  srf.pos.w = 200;                        // Width
  srf.pos.h = 100;                        // Height

  // Render the rectangle
  SDL_RenderFillRect(srf.win, &srf.pos);

  // Present the rendered image
  SDL_RenderPresent(srf.win);

  // Wait for 5 seconds
  //SDL_Delay(5000);

  connectToFirebase();

  // Clean up and close
  SDL_DestroyRenderer(srf.win);
  closeEverything();

  return 0;
}
