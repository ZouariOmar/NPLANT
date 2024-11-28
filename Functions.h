#ifndef FUNCTIONS
#define FUNCTIONS

#include "Global variables.h"

#define H 1080       // Height of the screen resolution
#define W 1920       // Width of the screen resolution
#define LenTxt 28    // Lenth of the input text

typedef struct Text{
    char Txt[LenTxt];
    TTF_Font* Font;
    SDL_Color Txt_Color;
    SDL_Surface* Surface_txt;
    SDL_Rect Txt_pos;
}Text;

/*
    > Structure containing Text features :
        - Message
        - Type of font
        - Text color
        - Surface of the text ( Will be converted to texture with "SDL_CreateTextureFromSurface")
        - Texture of the text
        - Text position
*/

typedef struct Button{
    SDL_Texture* img;
    SDL_Rect pos;
}Button;

/*
    > Structure containing button features :
        - Image of the button
        - Position of the button
*/

typedef struct UI{
    SDL_Texture* Background;
    Button Link; 
    Text Input;
}UI;

/*
    > Structure containing the UI specificities :
        - Background image
        - Link image ( When mouse is over it )
        - Position of the image of the link
        - Text input
*/

///////////////////////////////////////////////////////////////

void InitSDL(void);

void InitTxtColor(SDL_Color* Color);

void CreateTxtSurface(Text* Message);

void InitTxt(Text* Message);

void InitUI(UI* Interface);

void UpdateInput(Text* Input);

void RenderUI(UI Interface);

void SDLFree(void);

#endif