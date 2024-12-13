#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    SDL_FreeSurface(Interface->Error.Surface_txt);
    SDL_DestroyTexture(Interface->Error.Texture_txt);
    SDL_FreeSurface(Interface->Input.Surface_txt);
    SDL_DestroyTexture(Interface->Input.Texture_txt);
    SDL_FreeSurface(Interface->Output.Surface_txt);
    SDL_DestroyTexture(Interface->Output.Texture_txt);
    SDL_DestroyRenderer(Render);
    SDL_DestroyWindow(Window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

//////////////////////////////////////////////////////////////////////////

void InitTxtColor(SDL_Color* Color, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    Color->r = r;
    Color->g = g;
    Color->b = b;
    Color->a = a;
}

//////////////////////////////////////////////////////////////////////////

void InitTxtPos(SDL_Rect* pos, int x, int y, int w, int h) {
    pos->x = x;
    pos->y = y;
    pos->w = w;
    pos->h = h;
}

//////////////////////////////////////////////////////////////////////////

void InitInput(Text* Input) {
    Input->Font = TTF_OpenFont("Font/ARIAL.TTF", 30);
    if (!(Input->Font)) {
        printf("> Erreur lors du chargement de la police 'input' : %s\n", TTF_GetError());
        return ;
    }

    // Init input content to empty string
    strcpy(Input->Txt, "");

    // Init colors of the input
    InitTxtColor(&(Input->Txt_Color), 255, 255, 255, 255);

    // Init input position
    InitTxtPos(&(Input->Txt_pos), 180, 230, 0, 0);

    // Init text surface
    Input->Surface_txt = NULL;
    Input->Texture_txt = NULL;
}

//////////////////////////////////////////////////////////////////////////

void InitOutput(Text* Output) {
    Output->Font = TTF_OpenFont("Font/ARIAL.TTF", 25);
    if (!(Output->Font)) {
        printf("> Erreur lors du chargement de la police 'output' : %s\n", TTF_GetError());
        return ;
    }

    // Init output content to empty string
    strcpy(Output->Txt, "");

    // Init colors of the output
    InitTxtColor(&(Output->Txt_Color), 255, 255, 255, 255);

    // Init output position
    InitTxtPos(&(Output->Txt_pos), 111, 508, 0, 0);

    // Init text surface
    Output->Surface_txt = NULL;
    Output->Texture_txt = NULL;
}

//////////////////////////////////////////////////////////////////////////

void InitError(Text* Error) {
    Error->Font = TTF_OpenFont("Font/ARIAL.TTF", 30);
    if (!(Error->Font)) {
        printf("> Erreur lors du chargement de la police 'erreur' : %s\n", TTF_GetError());
        return ;
    }
    
    // Init error text content to empty string
    strcpy(Error->Txt, "Erreur : 28 caracteres maximum");

    // Init colors of the error text
    InitTxtColor(&(Error->Txt_Color), 200, 0, 0, 0);

    // Init error text position
    InitTxtPos(&(Error->Txt_pos), 370, 304, 430, 34);

    // Init text surface
    Error->Surface_txt = TTF_RenderText_Solid(Error->Font, Error->Txt, Error->Txt_Color);
    if(!Error->Surface_txt){
        printf("> Erreur lors de la creation de la surface du texte : %s\n", TTF_GetError());
        return;
    }

    // Create new text texture
    Error->Texture_txt = SDL_CreateTextureFromSurface(Render, Error->Surface_txt);
    if(!Error->Texture_txt)
        printf("> Erreur lors de la création de la texture du texte : %s\n", SDL_GetError());
}

//////////////////////////////////////////////////////////////////////////

void InitBackgroundimages(BG* Background) {
    Background->BG_Unselect = IMG_LoadTexture(Render, "Assets/Background.png");
    Background->BG_Select = IMG_LoadTexture(Render, "Assets/Background link selected.png");
}

//////////////////////////////////////////////////////////////////////////

void InitButtonPos(BG* Background) {
    Background->Btn_pos.x = 97;
    Background->Btn_pos.y = 291;
    Background->Btn_pos.w = 250;
    Background->Btn_pos.h = 62;
}

//////////////////////////////////////////////////////////////////////////

void InitBackground(BG* Background) {
    // Init background images
    InitBackgroundimages(Background);

    // Init link button position
    InitButtonPos(Background);
}

//////////////////////////////////////////////////////////////////////////

void InitUI(UI* Interface) {
    // Init Input
    InitInput(&(Interface->Input));

    // Init Output
    InitOutput(&(Interface->Output));

    // Init Error message
    InitError(&(Interface->Error));

    // Init background images
    InitBackground(&(Interface->Background));
    
    // Init error output
    Interface->Check_Error = 0;

    // Init Press button
    Interface->Btn_press = 0;
}

//////////////////////////////////////////////////////////////////////////

void UpdateInput(UI* Interface) {
    char c;
    int Input_l = strlen(Interface->Input.Txt);
    int sym = (int)(Event.key.keysym.sym);

    // If the ASCII code between A and z and length of the input text < LenTxt (max characters) => Add the character to the input text
    if((Event.key.keysym.sym >= 33 && Event.key.keysym.sym <= 126) && (Input_l<LenTxt)){
        // Reinitialize the check error
        if(Interface->Check_Error)
            Interface->Check_Error = 0;

        // Check paste command
        if(Event.key.keysym.mod & KMOD_CTRL && Event.key.keysym.sym == SDLK_v) {
            if(strlen(SDL_GetClipboardText())>28){
                Interface->Check_Error = 1;
                strcpy(Interface->Input.Txt, "");
            }
            else
                strcpy(Interface->Input.Txt, SDL_GetClipboardText());          
        }
            

        // Check normal input
        else {
            // Check if it's a capital letter or not
            if(Event.key.keysym.mod & KMOD_SHIFT || Event.key.keysym.mod & KMOD_CAPS)
                c = (char)(sym - 32);     
            else
                c = (char)sym;

            Interface->Input.Txt[Input_l] = c;
            Interface->Input.Txt[Input_l+1] = '\0';
        }

    }
    
    // If the ASCII code is the backspace then delete the last character
    else if(Event.key.keysym.sym == SDLK_BACKSPACE)
        Interface->Input.Txt[Input_l-1] = '\0';
}

//////////////////////////////////////////////////////////////////////////

void UpdateTxtTexture(Text* Text) {

    // Free the old text surface
    if(Text->Surface_txt){
        SDL_FreeSurface(Text->Surface_txt);
        Text->Texture_txt = NULL;
    }

    // Free the old text texture
    if(Text->Texture_txt)
        SDL_DestroyTexture(Text->Texture_txt);

    // Create new text surface
    Text->Surface_txt = TTF_RenderText_Solid(Text->Font, Text->Txt, Text->Txt_Color);
    if(!Text->Surface_txt){
        printf("> Erreur lors de la creation de la surface du texte : %s\n", TTF_GetError());
        return;
    }

    // Update the width and lenght of the text
    Text->Txt_pos.w = Text->Surface_txt->w;
    Text->Txt_pos.h = Text->Surface_txt->h;

    // Create new text texture
    Text->Texture_txt = SDL_CreateTextureFromSurface(Render, Text->Surface_txt);
    if(!Text->Texture_txt)
        printf("> Erreur lors de la création de la texture du texte : %s\n", SDL_GetError());
    
}

//////////////////////////////////////////////////////////////////////////

void UpdateTxtRendering(UI* Interface) {
    // Update text content through input detection
    UpdateInput(Interface);

    // Update input text texture
    UpdateTxtTexture(&(Interface->Input));

    // Update output text texture
    UpdateTxtTexture(&(Interface->Output));
}

//////////////////////////////////////////////////////////////////////////

void CheckLinkButton(UI* Interface) {
    if(Event.motion.x > 97 && Event.motion.x < 173 + WidthBUTTON){
        if(Event.motion.y > 291  && Event.motion.y < 291 + HeightBUTTON){
            // Change color of the link button
            SDL_RenderCopy(Render, Interface->Background.BG_Select, &(Interface->Background.Btn_pos), &(Interface->Background.Btn_pos));

            // Check if the button hasb been pressed
            if(Event.type == SDL_MOUSEBUTTONDOWN)
                Interface->Btn_press = 1;
        }
    }
}

//////////////////////////////////////////////////////////////////////////

void RenderUI(UI* Interface) {
    // UI background rendering
    SDL_RenderCopy(Render, Interface->Background.BG_Unselect, NULL, NULL);

    // Check button rendering + click
    CheckLinkButton(Interface);

    // Input rendering
    SDL_RenderCopy(Render, Interface->Input.Texture_txt, NULL, &(Interface->Input.Txt_pos));

    // Output rendering
    if(Interface->Btn_press)
        SDL_RenderCopy(Render, Interface->Output.Texture_txt, NULL, &(Interface->Output.Txt_pos));

    // Error rendering
    if(Interface->Check_Error)
        SDL_RenderCopy(Render, Interface->Error.Texture_txt, NULL, &(Interface->Error.Txt_pos));

    // Render the new frame to the screen
    SDL_RenderPresent(Render);
}

//////////////////////////////////////////////////////////////////////////