#include <stdio.h>
#include "Functions.h"


// Compile command : gcc -o bin/main.exe main.c Functions.c -I ./Src/include -L ./Src/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
// Execute : ./bin/main

int main( int argc, char* argv[] )
{
    SDL_Window* window = NULL;
    SDL_Renderer* Render = NULL; // Utility ?
    SDL_Event Event;

    int Run = 1;

    InitSDL(&window, &Render);

    SDL_Texture* img = IMG_LoadTexture(Render, "Assets/Test_img.png");

    printf("> Generation completed\n\n");

    while(Run)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT || Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE)
                Run = 0;
        }

        SDL_RenderCopy(Render, img, NULL, NULL);
        SDL_RenderPresent(Render);
        //SDL_UpdateWindowSurface(window); // Why ? What difference with render present ?
    }

    SDL_DestroyRenderer(Render);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}