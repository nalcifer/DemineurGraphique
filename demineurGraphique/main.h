#pragma once

// init fonction et struct
SDL_Texture* initImage(const char* src,  SDL_Texture* image_texture, SDL_Renderer* renderer);
void displayImage(SDL_Texture* image, SDL_Rect image_location, SDL_Renderer* renderer);