#include <stdio.h>
#include <stdlib.h>
#include "Functions.h"

SDL_Window* Window = NULL;
SDL_Renderer* Render = NULL;
SDL_Event Event;

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

//////////////////////////////////////////////////////////////////////////

void SDLFree(UI* Interface) {
    SDL_FreeSurface(Interface->Input.Surface_txt);
    SDL_DestroyTexture(Interface->Input.Texture_txt);
    SDL_DestroyRenderer(Render);
    SDL_DestroyWindow(Window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

//////////////////////////////////////////////////////////////////////////

void InitTxtColor(SDL_Color* Color) {
    Color->r = 255;
    Color->g = 255;
    Color->b = 255;
    Color->a = 255;
}

//////////////////////////////////////////////////////////////////////////

void InitTxtPos(SDL_Rect* pos){
    pos->x = 200;
    pos->y = 200;
    pos->w = 0;
    pos->h = 0;
}

//////////////////////////////////////////////////////////////////////////

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

    // Init text position
    InitTxtPos(&(Input->Txt_pos));

    // Init text surface
    Input->Surface_txt = NULL;
    Input->Texture_txt = NULL;
}

//////////////////////////////////////////////////////////////////////////

void InitTA(TA* Link) {
    // Init the link TA image
    Link->img = IMG_LoadTexture(Render, "Assets/Link_img.jpeg");

    // Init the link TA position
    // !! NEED TO CHECK PSD FILE !!
    Link->pos.x = 200;
    Link->pos.y = 200;
    Link->pos.w = 400;
    Link->pos.h = 50;
}

//////////////////////////////////////////////////////////////////////////

void InitUI(UI* Interface) {
    // Init Text
    InitInput(&(Interface->Input));

    // Init background image
    Interface->Background = IMG_LoadTexture(Render, "Assets/Wallpaper.jpg");

    // Init link TA
    InitTA(&(Interface->Link));
}

//////////////////////////////////////////////////////////////////////////

void UpdateInput(char Txt[]) {
    char c;
    int Input_l = strlen(Txt);
    int sym = (int)(Event.key.keysym.sym);

    // If the ASCII code between a and z and length of the input text < LenTxt (max characters) => Add the character to the input text
    if((Event.key.keysym.sym >= 33 && Event.key.keysym.sym <= 126) && (Input_l<LenTxt)){
        if(Event.key.keysym.mod & KMOD_SHIFT ||Event.key.keysym.mod & KMOD_CAPS)
            c = (char)(sym - 32);     
        else
            c = (char)sym;

        printf("%c\n",c);
        Txt[Input_l] = c;
        Txt[Input_l+1] = '\0';
    }
    
    // If the ASCII code is the backspace then delete the last character
    else if(Event.key.keysym.sym == SDLK_BACKSPACE)
        Txt[Input_l-1] = '\0';
}

//////////////////////////////////////////////////////////////////////////

void UpdateTxtTexture(Text* Input) {

    // Free the old text surface
    if(Input->Surface_txt){
        SDL_FreeSurface(Input->Surface_txt);
        Input->Texture_txt = NULL;
    }

    // Free the old text texture
    if(Input->Texture_txt)
        SDL_DestroyTexture(Input->Texture_txt);

    // Create new text surface
    Input->Surface_txt = TTF_RenderText_Solid(Input->Font, Input->Txt, Input->Txt_Color);
    if(!Input->Surface_txt){
        printf("> Erreur lors de la création de la surface du texte : %s\n", TTF_GetError());
        return;
    }

    // Update the width and lenght of the text
    Input->Txt_pos.w = Input->Surface_txt->w;
    Input->Txt_pos.h = Input->Surface_txt->h;

    // Create new text texture
    Input->Texture_txt = SDL_CreateTextureFromSurface(Render, Input->Surface_txt);
    if(!Input->Texture_txt)
        printf("> Erreur lors de la création de la texture du texte : %s\n", SDL_GetError());
    
}

//////////////////////////////////////////////////////////////////////////

void UpdateTxtRendering(Text* Input) {
    // Update text content through input detection
    UpdateInput(Input->Txt);

    // Update text texture
    UpdateTxtTexture(Input);
}

//////////////////////////////////////////////////////////////////////////

void RenderUI(UI Interface) {
    // Prepare UI background rendering
    SDL_RenderCopy(Render, Interface.Background, NULL, NULL);

    // Prepare Link background rendering
    SDL_RenderCopy(Render, Interface.Link.img, &Interface.Link.pos, &Interface.Link.pos);

    // Prepare text rendering
    SDL_RenderCopy(Render, Interface.Input.Texture_txt, NULL, &(Interface.Input.Txt_pos));

    // Render the new frame to the screen
    SDL_RenderPresent(Render);
}

//////////////////////////////////////////////////////////////////////////