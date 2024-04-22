#ifndef SDL_DECK_H
#define SDL_DECK_H

#include "../controller/controller.h"
#include "../model/deck.h"
#include "sdl_cards.h"

void SDL_initdeck(Controller *ctrl, SDL_CardManager *sdl_cm);

ll_node_card *CheckCardHover(Controller *ctrl, struct nk_input *nk_inp, SDL_CardManager *sdl_cm);

void CardEventHandler(SDL_Event *evt, Controller *ctrl, struct nk_input *nk_inp, SDL_CardManager *sdl_cm);

#endif
