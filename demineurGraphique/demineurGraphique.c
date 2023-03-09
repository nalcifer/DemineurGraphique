#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"


int main(int argc, char* argv[]){

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* surface;
    SDL_Rect title_location = { 270, 0, 440, 350 };
    SDL_Rect axolotl_location = { 380, 250, 230, 200 };
    SDL_Color purple = { 161, 126, 194, 255 };
    SDL_Color lightPurple = { 216, 189, 232, 255 };

    int statut = EXIT_FAILURE;
    // initialisation SDL
    if (0 != SDL_Init(SDL_INIT_EVERYTHING)) {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }
    // creation fenetre
    window = SDL_CreateWindow("Dexolot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 940, 680, SDL_WINDOW_OPENGL);
    // creation rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    ///* initialisation SDL_ttf (texte) */
    //if (TTF_Init() < 0)
    //{
    //    printf("Impossible d'initialiser SDL_ttf : %s", SDL_GetError());
    //    return 1;
    //}
    //TTF_Font* Font = TTF_OpenFont("comic.ttf", 50);
    // couleur background
    SDL_SetRenderDrawColor(renderer, lightPurple.r, lightPurple.g, lightPurple.b, lightPurple.a);
    // icon
    surface = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    // images
    displayImage("img/title.png", title_location, renderer);
    displayImage("img/axolot.gif", axolotl_location, renderer);
    /* on agit sur la fenêtre ici */
    SDL_RenderPresent(renderer);
    SDL_SetWindowIcon(window, surface);
    SDL_bool program_launch = SDL_TRUE;
    while (program_launch) {
        //event
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                program_launch = SDL_FALSE;
                break;

            default:
                break;
            }
        }
        


    }
    statut = EXIT_SUCCESS;
    //------------------------------
Quit:
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
}

void displayImage(const char* src, SDL_Rect image_location, SDL_Renderer* renderer) {
    SDL_Surface* image = IMG_Load(src);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    SDL_RenderCopy(renderer, texture, NULL, &image_location);
}