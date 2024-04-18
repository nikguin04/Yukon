#ifndef sdl_image_loader_h
#define sdl_image_loader_h

#include "sdlmanager.h"

SDL_Texture *LoadOptimizedImage(char *path, SDL_Surface *gScreenSurface, SDL_Renderer *rend);
SDL_Texture *LoadSDLImage(char *path, SDL_Renderer *rend);

#endif