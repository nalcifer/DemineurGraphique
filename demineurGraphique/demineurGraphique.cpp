#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    int statut = EXIT_FAILURE;
    SDL_Color purple = { 161, 126, 194, 255 };
    if (0 != SDL_Init(SDL_INIT_EVERYTHING)) {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }
    // creation fenetre
    window = SDL_CreateWindow("Demineur uwu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_SHOWN| SDL_WINDOW_RESIZABLE);
    if (NULL == window){
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
    }
    // creation rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        goto Quit;
    }

    // couleur
    if (0 != SDL_SetRenderDrawColor(renderer, purple.r, purple.g, purple.b, purple.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        goto Quit;
    }

    if (0 != SDL_RenderClear(renderer))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        goto Quit;
    }

    /* on agit sur la fenêtre ici */
    SDL_Delay(1000);
    SDL_RenderPresent(renderer);
    SDL_Delay(500);
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

