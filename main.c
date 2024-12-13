#include <stdio.h>
#include "Functions.h"

/*
* (1) Automatic program compilation and execution :
*      - "make" on Linux/Unix
*      - "mingw32-make.exe" on Windows 
* (2) Manual command : gcc -o bin/main.exe main.c Functions.c -I ./Src/include -L ./Src/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
* (2) Manual execution : ./bin/main
*/

int main( int argc, char* argv[] )
{
    UI Interface;
    int Run = 1;

    // Global Intialization
    InitSDL();
    InitUI(&Interface);

    while(Run)
    {
        while(SDL_PollEvent(&Event))
        {
            // Close the program if the user clicks on the "ESCAPE" key or on the "close window" button
            if(Event.type == SDL_QUIT || Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE)
                Run = 0;
            
            // Manage other key inputs
            else if(Event.type == SDL_KEYDOWN)
                UpdateTxtRendering(&Interface);
            
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