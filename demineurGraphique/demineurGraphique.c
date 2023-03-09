#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"


int main(int argc, char* argv[]){

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* surface;
    SDL_Texture* image_texture = NULL;
    SDL_Rect title_location = { 270, 0, 440, 350 };
    SDL_Rect axolotl_location = { 380, 250, 230, 200 };
    SDL_Color purple = { 161, 126, 194, 255 };
    SDL_Color lightPurple = { 216, 189, 232, 255 };
    //textes init
    TTF_Font* font = TTF_OpenFont("font/comic.ttf", 50);
    SDL_Color text_color = { 255, 0, 0, 255 };
    SDL_Surface* message = TTF_RenderText_Solid(font, "Salut tout le monde !", text_color);
    SDL_Rect text_location = { 0, 0, 230, 200 };

    int statut = EXIT_FAILURE;
    // initialisation SDL
    if (0 != SDL_Init(SDL_INIT_EVERYTHING)) {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }
    TTF_Init();
    // creation fenetre
    window = SDL_CreateWindow("Dexolot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 940, 680, SDL_WINDOW_OPENGL);
    // creation rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // couleur background
    SDL_SetRenderDrawColor(renderer, lightPurple.r, lightPurple.g, lightPurple.b, lightPurple.a);
    // icon
    surface = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    // images
    SDL_Texture* title_texture = initImage("img/title.png", image_texture, renderer);
    SDL_Texture* axolotl_texture = initImage("img/axolot.gif", image_texture, renderer);
    displayImage(title_texture, title_location, renderer);
    displayImage(axolotl_texture, axolotl_location, renderer);
    // textes
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, message);
    SDL_DestroyTexture(text);
    SDL_FreeSurface(message);
    SDL_RenderCopy(renderer, text, NULL, &text_location);
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
        

        TTF_CloseFont(font);

    }
    statut = EXIT_SUCCESS;
    //------------------------------
Quit:
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return statut;
}

SDL_Texture* initImage(const char* src, SDL_Texture* image_texture, SDL_Renderer* renderer) {
    SDL_Surface* image = IMG_Load(src);
    image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}
void displayImage(SDL_Texture* image_texture, SDL_Rect image_location, SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, image_texture, NULL, &image_location);
}