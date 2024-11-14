#include <stdio.h>
#include <SDL2/SDL.h>
#include "Functions.h"


// Compile command : gcc -o bin/main.exe main.c Functions.c -I ./Src/include -L ./Src/lib -lmingw32 -lSDL2main -lSDL2
// Execute : ./bin/main

int main( int argc, char* argv[] )
{
    SDL_Window *window = NULL;
    SDL_Renderer *Render = NULL;
    SDL_Event Event;
    int Run = 1;

    InitSDL(&window, &Render);

    printf("> Generation completed\n\n");

    while(Run)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT || Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE)
                Run = 0;
        }
    }

    SDL_DestroyRenderer(Render);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}