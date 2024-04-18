#ifndef sdl_deck_h
#define sdl_deck_h

#include "../controller/controller.h"
#include "../model/deck.h"
#include "sdl_cards.h"

void SDL_initdeck(Controller *ctrl, SDL_Cardmanager *sdl_cm);

void CheckCardHover(Controller *ctrl, struct nk_input *nk_inp, SDL_Cardmanager *sdl_cm);

#endif