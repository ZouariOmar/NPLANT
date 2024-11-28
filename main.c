#include <stdio.h>
#include "Functions.h"

// Compile command : gcc -o bin/main.exe main.c Functions.c -I ./Src/include -L ./Src/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
// Execute : ./bin/main

int main( int argc, char* argv[] )
{
    UI Interface;
    int Run = 1;

    InitSDL();
    InitUI(&Interface);

    while(Run)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT || Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE)
                Run = 0;
            
            else if(Event.type == SDL_KEYDOWN){}
                UpdateTxtRendering(&(Interface.Input));
            
            // Render UI
            RenderUI(Interface);
        }

        // Delay
        SDL_Delay(100);
    }

    SDLFree();

    return 0;
}