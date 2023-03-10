#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#define row 100
int i, j;

int main(int argc, char* argv[]){

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* surface;
    SDL_Texture* image_texture = NULL;
    SDL_Rect title_location = { 270, 0, 440, 350 };
    SDL_Rect axolotl_location = { 380, 250, 230, 200 };
    SDL_Color purple = { 161, 126, 194, 255 };
    SDL_Color lightPurple = { 216, 189, 232, 255 };
    Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) ;
    Mix_Music* music = Mix_LoadMUS("music.mp3");
    //textes init
    TTF_Font* font = TTF_OpenFont("font/comic.ttf", 50);
    SDL_Color text_color = { 255, 0, 0, 255 };
    SDL_Surface* message = TTF_RenderText_Solid(font, "PRESS SPACE TO START !", text_color);
    SDL_Rect text_location = { 0, 0, 230, 200 };

    int statut = EXIT_FAILURE;
    // initialisation SDL
    if (0 != SDL_Init(SDL_INIT_EVERYTHING)) {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }
    // initialisation son
    Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_PlayMusic(music, -1);
    Uint8 volume = 10;
    Mix_VolumeMusic(volume);
    // initialisation texte
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
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
                    Mix_PauseMusic(); // Mets en pause la musique 
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
                    Mix_ResumeMusic(); // Reprend la lecture 
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
                    Mix_RewindMusic(); // Revient au début de la musique
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP && volume < MIX_MAX_VOLUME)
                    volume++; // Augmente le volume jusqu'a MIX_MAX_VOLUME
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN && volume > 0)
                    volume--; // Réduit le volume jusqu'a 0
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                    Mix_HaltMusic(); // Arreter la musique

            case SDL_KEYDOWN:
                
                if (event.type == SDL_KEYDOWN)
                    Mix_VolumeMusic(volume); // Applique le volume desirer
                if (event.key.keysym.sym == SDLK_SPACE)
                {
                    SDL_RenderClear(renderer);
                    SDL_Rect axolotl_location = { 600, 250, 230, 200 };
                    displayImage(axolotl_texture, axolotl_location, renderer);
                    SDL_Rect tab[105]; // déclaration du tableau contenant les tab
                    SDL_SetRenderDrawColor(renderer, purple.r, purple.g, purple.b, SDL_ALPHA_OPAQUE);
                    tab[0].x = 70;
                    tab[0].y = 150;
                    tab[0].w = tab[0].h = 40;
                    for (int i = 1; i < row; i++) {
                        for (j = 0; j < row; ++j) {
                            tab[i].x = tab[i - 1].x + 45;
                            tab[i].y = tab[i - 1].y;
                            if ((i % 10 == 0)) //retour à la ligne impair
                            {
                                tab[i].x = 0 + 70;
                                tab[i].y = tab[i - 1].y + 45;
                            }
                            tab[i].w = tab[i].h = 40; //taille d'une case
                        }
                        SDL_RenderFillRects(renderer, tab, 100);
                        SDL_RenderPresent(renderer);
                    }
                }
                
                break;
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
    Mix_FreeMusic(music);
    Mix_CloseAudio();
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