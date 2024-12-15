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

// int main() {
//   __lance__();
//   return 0;
// }

/**
 * @brief # The Main program function
 * @return int
 */
int main() {
  UI Interface;
  int Run = 1;

  // Global Intialization
  InitSDL();
  InitUI(&Interface);

  while (Run) {
    while (SDL_PollEvent(&Event)) {
      // Close the program if the user clicks on the "ESCAPE" key or on the "close window" button
      if (Event.type == SDL_QUIT || (Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE))
        Run = 0;

      // Manage other key inputs
      else if (Event.type == SDL_KEYDOWN)
        UpdateTxtRendering(&Interface);

      //! testing case
      if (Interface.Btn_press) {
        connectToFirebase(Interface.Input.Txt, Interface.Output.Txt);
        printf("%s\n", Interface.Output.Txt);
        Interface.Btn_press = 0;
      }

      // Render UI
      RenderUI(&Interface);
    }

    // Delay of 100ms
    SDL_Delay(100);
  }

  // Frees the program
  SDLFree(&Interface);

  return 0;
}