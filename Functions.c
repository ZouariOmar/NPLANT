#include <stdio.h>
#include <stdlib.h>
#include "Functions.h"

SDL_Window* Window = NULL;
SDL_Renderer* Render = NULL;
SDL_Event Event;

/* -------------- INIT AND FREE SDL -------------- */

void InitSDL(void) {
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("> ERREUR : Initialisation SDL > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
    {
        SDL_Log("> ERREUR : Initialisation SDL_IMG > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if(TTF_Init())
    {
        SDL_Log("> ERREUR : Initialisation SDL_ttf > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    Window = SDL_CreateWindow("Première fenêtre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0);

    if(!(Window))
    {
        SDL_Log("> ERREUR : Initialisation SDL > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    Render = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

    if(!(Render))
    {
        SDL_Log("> Erreur : Initialisation Renderer > %s\n", SDL_GetError());
        SDL_DestroyWindow(Window);
        exit(EXIT_FAILURE);
    }
}

void SDLFree(void) {
    SDL_DestroyRenderer(Render);
    SDL_DestroyWindow(Window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

/* ================= INITIALIZATION OF THE INTERFACE ================= */

/* -------------- INPUT INITIALIZATION -------------- */

void InitTxtColor(SDL_Color* Color) {
    Color->r = 255;
    Color->g = 255;
    Color->b = 255;
    Color->a = 255;
}

void CreateTxtSurface(Text* Input) {
    // Init Input surface
    Input->Surface_txt = TTF_RenderText_Solid(Input->Font,Input->Txt,Input->Txt_Color);
    if(!Input->Surface_txt)
        printf("> Erreur lors de la création du texte : %s\n", TTF_GetError());
}

void InitInput(Text* Input) {
    Input->Font = TTF_OpenFont("Font/ARIAL.TTF", 24);
    if (!(Input->Font)) {
        printf("> Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return ;
    }

    // Init Text content to empty string
    strcpy(Input->Txt, "");

    // Init colors of the text
    InitTxtColor(&(Input->Txt_Color));

    // Create the surface of the text
    CreateTxtSurface(Input);
    
}

/* -------------- LINK BUTTON INITIALIZATION -------------- */

void InitButton(Button* Link) {
    // Init the link button image
    Link->img = IMG_LoadTexture(Render, "Assets/Link_img.jpeg");

    // Init the link button position
    // !! NEED TO CHECK PSD FILE !!
    Link->pos.x = 200;
    Link->pos.y = 200;
    Link->pos.w = 400;
    Link->pos.h = 50;
}

/* -------------- UI INITIALIZATION -------------- */

void InitUI(UI* Interface) {
    // Init Text
    InitInput(&(Interface->Input));

    // Init background image
    Interface->Background = IMG_LoadTexture(Render, "Assets/Wallpaper.jpg");

    // Init link button
    InitButton(&(Interface->Link));
}

/* ================= INPUT UPDATE ================= */

void UpdateInput(Text* Input){
    char c;
    int Input_l = strlen(Input->Txt);

    //
    if((Event.key.keysym.sym >= 33 && Event.key.keysym.sym <= 126) && (Input_l<LenTxt)){
        c = (char)Event.key.keysym.sym;
        Input->Txt[Input_l] = c;
        Input->Txt[Input_l+1] = '\0';
    }
    
    else if(Event.key.keysym.sym == SDLK_BACKSPACE){
        Input->Txt[Input_l-1] = '\0';
        //Input->Txt[Input_l+1] = '\0';
    }

    printf("Input : %s\n", Input->Txt);
}

/* ================= RENDERING ================= */

/* -------------- INTERFACE RENDERING  -------------- */

void RenderUI(UI Interface) {
    // Prepare UI background rendering
    SDL_RenderCopy(Render, Interface.Background, NULL, NULL);

    // Prepare Link background rendering
    SDL_RenderCopy(Render, Interface.Link.img, &Interface.Link.pos, &Interface.Link.pos);

    // 
    SDL_RenderPresent(Render);
}