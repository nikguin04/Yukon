#include "sdl_deck.h"
#include "linkedlist.h"
#include "yukon_model.h"
#include <SDL_events.h>
#include <SDL_mouse.h>
#include <stdio.h>

// TODO: This should call the proper lock deck with path, and init the sdl texture arrays, etc.. after
void SDL_initdeck(Controller *ctrl, SDL_CardManager *sdl_cm) {
	// TEMP INIT OF DECK
	const char *msg;
	ctrl->model->deck = LoadDeck("", &msg);
	DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_STARTSIZE);

	for (int a = 0; a < NUM_COLUMNS; a++) {
		ll_node_card *curcard = ctrl->model->yukon->columnFront[a];
		while (curcard != NULL) {
			int index = GetCardAbsoluteIndex(curcard->card);
			struct nk_rect nkr = {0, 0, 0, 0};
			sdl_cm->cardRects[index] = nkr;
			sdl_cm->cardRefs[index] = curcard;
			curcard = curcard->next;
		}
	}
}

ll_node_card *CheckCardHover(Controller *ctrl, struct nk_input *nk_inp, SDL_CardManager *sdl_cm) {
	for (int a = 0; a < NUM_COLUMNS; a++) { // Check columns
		ll_node_card *curcard = ctrl->model->yukon->columnFront[a];
		ll_node_card *hover = NULL;
		while (curcard != NULL) {
			int index = GetCardAbsoluteIndex(curcard->card);

			if (nk_input_is_mouse_hovering_rect(nk_inp, sdl_cm->cardRects[index])) {
				hover = curcard; // This will loop to last card in column
			}

			curcard = curcard->next;
		}
		if (hover != NULL) return hover;
	}

	for (int a = 0; a < NUM_FOUNDATIONS; a++) { // Check foundations
		//sdl_cm->foundationRects[i]
		if (nk_input_is_mouse_hovering_rect(nk_inp, sdl_cm->foundationRects[a])) {
			hover = ctrl->model->yukon->foundationPile[a]; // This will loop to last card in column
		}
	}
	return NULL;
}

void CardEventHandler(SDL_Event *evt, Controller *ctrl, struct nk_input *nk_inp, SDL_CardManager *sdl_cm) {
	// NOTE: Needs extra arg that tells if a card has been picked up, and if so which
	SDL_MouseButtonEvent mouse_evt = evt->button;
	if (mouse_evt.button != SDL_BUTTON_LEFT) return;
	ll_node_card *hover = CheckCardHover(ctrl, nk_inp, sdl_cm);
	if (hover == NULL) return;
	char cardstr[8];
	CardToString(hover->card, cardstr);
	printf("Mouse event (%s) on card: %s\n", (evt->type == SDL_MOUSEBUTTONDOWN ? "DOWN" : "UP"), cardstr);
}
