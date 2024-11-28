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
    SDL_Texture* Texture_txt;
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

typedef struct TextArea{
    SDL_Texture* img;
    SDL_Rect pos;
}TA;

/*
    > Structure containing the text area features :
        - Image of the text area
        - Position of the text area
*/

typedef struct UserInterface{
    SDL_Texture* Background;
    TA Link; 
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

/* ================= INIT AND FREE SDL ================= */

// Initialization of SDL
void InitSDL(void);

// Free SDL + Surface and Texture memory allocations
void SDLFree(UI* Interface);

/* ================= INITIALIZATION OF THE INTERFACE ================= */

// Initialization of the color of the text (White)
void InitTxtColor(SDL_Color* Color);

// Initialization of the position of the text
void InitTxtPos(SDL_Rect* pos);

// Initialization of the text content ("")
void InitInput(Text* Message);

// Initialization of the link text area
void InitTA(TA* Link);

// Initialization of the User interface
void InitUI(UI* Interface);

/* ================= INPUT UPDATE ================= */

// Update of the users input
void UpdateInput(char Txt[]);

// Update of the input texture
void UpdateTxtTexture(Text* Input);

// Update of the input rendering
void UpdateTxtRendering(Text* Input);

/* ================= RENDERING ================= */

// Render the User inteface to the screen
void RenderUI(UI Interface);

//////////////////////////////////////////////////////////////////////////

#endif