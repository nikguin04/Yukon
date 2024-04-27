#ifndef SDL_IMAGE_LOADER_H
#define SDL_IMAGE_LOADER_H

#include "sdlmanager.h"

SDL_Texture *LoadOptimizedImage(char *path, SDL_Surface *gScreenSurface, SDL_Renderer *rend);
SDL_Texture *LoadSDLImage(char *path, SDL_Renderer *rend);

#endif
