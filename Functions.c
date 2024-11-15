#include <stdio.h>
#include <stdlib.h>
#include "Functions.h"

SDL_Window* Window = NULL;
SDL_Renderer* Render = NULL;
SDL_Event Event;

void InitSDL(void)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR : Initialisation SDL > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
    {
        SDL_Log("ERREUR : Initialisation SDL_IMG > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if(TTF_Init())
    {
        SDL_Log("ERREUR : Initialisation SDL_ttf > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    Window = SDL_CreateWindow("Première fenêtre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0);

    if(!(Window))
    {
        SDL_Log("ERREUR : Initialisation SDL > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    Render = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

    if(!(Render))
    {
        SDL_Log("Erreur : Initialisation Renderer > %s\n", SDL_GetError());
        SDL_DestroyWindow(Window);
        exit(EXIT_FAILURE);
    }
}

void InitFont(TTF_Font** Font)
{
 *Font = TTF_OpenFont("Font/ARIAL.TTF", 24);
    if (!(*Font)) {
        printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return ;
    }   
}

void SDLFree(void)
{
    SDL_DestroyRenderer(Render);
    SDL_DestroyWindow(Window);
    IMG_Quit();
    //TTF_Quit();
    SDL_Quit();
}