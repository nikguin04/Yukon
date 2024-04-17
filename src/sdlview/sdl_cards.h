#ifndef sdl_cards_h
#define sdl_cards_h

#include "sdlmanager.h"
#include <SDL_events.h>
#include <SDL_render.h>
#include "../model/deck.h"
#include "sdl_image_loader.h"
#include <SDL_render.h>
#include <SDL_surface.h>

void Cards_GetEvent(SDLManager *manager, SDL_Event *event);

SDL_Texture *card_textures[DECK_LENGTH]; // DECK_LENGTH
void initCard_Textures(SDL_Surface *gScreenSurface, SDL_Renderer *rend);

#endif