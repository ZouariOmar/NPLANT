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
#define PROJECT_NAME "IoT-Project"

//? -------------------- INCLUDE PROTOTYPE DECLARATION PART --------------------
//* STANDARD LIBS INCLUDE PART
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//* SDL2 INCLUDE PART
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>
//// #include <gif_lib.h>

//? --------------------- PUBLIC VARS DECLARATION PART ---------------------
//* SCREEN SURFACE DECLARATION
extern SDL_Window *window;

//* SCREEN RESOLUTION DECLARATION
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//* SDL_COLOR PUBLIC DECLARATION
extern const SDL_Color WHITE;
extern const SDL_Color BLACK;

//? --------------------- STRUCT PROTOTYPE DECLARATION PART ----------------------
typedef struct Surface {
  SDL_Renderer *win;
  SDL_Rect pos;
} surface;  // Surface struct

//? -------------------- FUNCTIONS PROTOTYPE DECLARATION PART --------------------
void initEverything();
void __lance__();
void setScreen(int);
SDL_Surface *load_img(const char *);
void closeEverything();

/**
 * @brief Load and freeing functions declaration part
 * @fn void set_pos(surface *, const char *, int)
 * @fn void loadResources(surface *, const char *, int, int)
 * @fn void freeResources(surface *, TTF_Font *, Mix_Chunk *, int)
 */

void set_pos(surface *, const char *, int);
void loadResources(surface *, const char *, int, int);
void freeResources(surface *, int);

#endif  // __INC_H__
