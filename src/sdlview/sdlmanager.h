#ifndef sdlmanager_h
#define sdlmanager_h

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_pixels.h>
#include <SDL_render.h>

typedef struct GUI_Struct_struct {
    SDL_Window *wind;
    TTF_Font* font;
    char* statusmsg;
    SDL_Surface *tempimg;
} SDLManager;

#endif