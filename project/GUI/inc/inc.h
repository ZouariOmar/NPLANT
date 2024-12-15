/**
 * @file inc.h
 * @author ZouariOmar (zouariomar20@gmail.com)
 * @brief The main declaration file
 * @version 0.1
 * @date 2024-10-03
 * @copyright Copyright (c) 2024
 */

//? -------------------- DEFINE PROTOTYPE DECLARATION PART --------------------
#ifndef __INC_H__
#define __INC_H__

#define MAX_PATH 260
#define PROJECT_NAME "NPLANT"
#define H 1080           // Height of the screen resolution
#define W 1920           // Width of the screen resolution
#define LenTxt 28        // Lenth of the input text
#define WidthBUTTON 170  // Width of the link button
#define HeightBUTTON 62  // Height of the link button

//? -------------------- INCLUDE PROTOTYPE DECLARATION PART --------------------
//* STANDARD LIBS INCLUDE PART
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//* SDL2 INCLUDE PART
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//? --------------------- STRUCT PROTOTYPE DECLARATION PART ----------------------

/*
    > Structure containing Text features :
        - Message
        - Type of font
        - Text color
        - Surface of the text ( Will be converted to texture with "SDL_CreateTextureFromSurface")
        - Texture of the text
        - Text position
*/
typedef struct Text {
  char Txt[LenTxt];  // User input
  TTF_Font* Font;
  SDL_Color Txt_Color;
  SDL_Surface* Surface_txt;
  SDL_Texture* Texture_txt;
  SDL_Rect Txt_pos;
} Text;

/*
    > Structure containing background features :
        - Background with unselected link button
        - Background with selected link button
        - Link button position
*/
typedef struct Background {
  SDL_Texture* BG_Unselect;
  SDL_Texture* BG_Select;
  SDL_Rect Btn_pos;
} BG;

/*
    > Structure containing the UI specificities :
        - Background images
        - User input
        - Check if the error message has to be shown
        - Check if the link button has been pressed
*/
typedef struct UserInterface {
  BG Background;
  Text Input;
  Text Output;
  Text Error;
  int connect;
  int Check_Error,
      Btn_press;
} UI;

//? --------------------- PUBLIC VARS DECLARATION PART ---------------------
//* SCREEN SURFACE DECLARATION
extern SDL_Window* Window;
extern SDL_Renderer* Render;
extern SDL_Event Event;

//* SCREEN RESOLUTION DECLARATION
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//* SDL_COLOR PUBLIC DECLARATION
extern const SDL_Color WHITE;
extern const SDL_Color BLACK;

//? -------------------- FUNCTIONS PROTOTYPE DECLARATION PART --------------------
void __lance__();

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

// Initialization of the output
void InitOutput(Text* Output);

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

// Update the image of the button and check if it has been pressed
void CheckLinkButton(UI* Interface);

/* ================= RENDERING ================= */

// Render the User inteface to the screen
void RenderUI(UI* Interface);

#endif  // __INC_H__
