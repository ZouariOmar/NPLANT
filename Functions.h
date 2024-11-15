#ifndef FUNCTIONS
#define FUNCTIONS

#include "Global variables.h"

#define H 1080       // Height of the screen resolution
#define W 1920       // Width of the screen resolution
#define iMax 1000     // Maximum iterations

typedef struct UI{
    SDL_Texture* Background;
    SDL_Texture* Link_img;
    SDL_Rect Link_pos;
}UI;

///////////////////////////////////////////////////////////////

void InitSDL(void);

void SDLFree(void);

#endif