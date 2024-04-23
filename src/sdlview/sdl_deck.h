#ifndef SDL_DECK_H
#define SDL_DECK_H

#include "../controller/controller.h"
#include "../model/deck.h"
#include "linkedlist.h"
#include "sdl_cards.h"

typedef struct pucard {
    bool active;
    bool is_column;
    int column_index;
    int foundation_index;
    ll_node_card *prev_pickup;
    ll_node_card *pickup;
} PickupCard;

void SDL_initdeck(Controller *ctrl, SDL_CardManager *sdl_cm);

void CheckCardHover(Controller *ctrl, struct nk_input *nk_inp, SDL_CardManager *sdl_cm, PickupCard *pucard);

void CardEventHandler(SDL_Event *evt, Controller *ctrl, struct nk_input *nk_inp, SDL_CardManager *sdl_cm, PickupCard *pucard);

#endif
