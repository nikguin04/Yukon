#ifndef sdl_cards_h
#define sdl_cards_h

#include <SDL_render.h>
#include "sdlmanager.h"
#include <SDL_events.h>
#include "../model/deck.h"
#include "sdl_image_loader.h"
#include <SDL_render.h>
#include <SDL_surface.h>
#include "deck.h"
#include <stdio.h> 

void Cards_GetEvent(SDLManager *manager, SDL_Event *event);

typedef struct SDL_Cardmanager_struct {
    SDL_Texture *card_textures[DECK_LENGTH];
} SDL_Cardmanager;

void initCard_Textures(SDL_Cardmanager *cardmanager, SDL_Surface *gScreenSurface, SDL_Renderer *rend);

#endif