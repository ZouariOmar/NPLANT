#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "Functions.h"

void InitSDL(SDL_Window** Window, SDL_Renderer** Render)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR : Initialisation SDL > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    *Window = SDL_CreateWindow("Première fenêtre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0);

    if(!(*Window))
    {
        SDL_Log("ERREUR : Initialisation SDL > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    *Render = SDL_CreateRenderer(*Window, -1, SDL_RENDERER_ACCELERATED);

    if(!(*Render))
    {
        SDL_Log("Erreur : Initialisation Renderer > %s\n", SDL_GetError());
        SDL_DestroyWindow(*Window);
        exit(EXIT_FAILURE);
    }
}