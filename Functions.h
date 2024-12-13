#ifndef FUNCTIONS
#define FUNCTIONS

#include "Global variables.h"

#define H 1080       // Height of the screen resolution
#define W 1920       // Width of the screen resolution
#define LenTxt 28    // Lenth of the input text
#define WidthBUTTON 170   // Width of the link button
#define HeightBUTTON 62   // Height of the link button

typedef struct Text{
    // User input
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

typedef struct Background{
    SDL_Texture* BG_Unselect;
    SDL_Texture* BG_Select;
    SDL_Rect Btn_pos;
}BG;

/*
    > Structure containing background features :
        - Background with unselected link button
        - Background with selected link button
        - Link button position
*/

typedef struct UserInterface{
    BG Background;
    Text Input;
    Text Error;
    int Check_Error,
        Btn_press;
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
void InitTxtColor(SDL_Color* Color, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

// Initialization of the position of the text
void InitTxtPos(SDL_Rect* pos, int x, int y, int w, int h);

// Initialization of the input
void InitInput(Text* Input);

// Initialization of the error
void InitError(Text* Error);

// Initialization of the User interface
void InitUI(UI* Interface);

/* ================= INPUT UPDATE ================= */

// Update of the users input
void UpdateInput(UI* Interface);

// Update of the input texture
void UpdateTxtTexture(Text* Input);

// Update of the input rendering
void UpdateTxtRendering(UI* Interface);

/* ================= BUTTON UPDATE ================= */

// Update the image of the button
void CheckLinkButton(UI Interface);

/* ================= RENDERING ================= */

// Render the User inteface to the screen
void RenderUI(UI Interface);

//////////////////////////////////////////////////////////////////////////

#endif