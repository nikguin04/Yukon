#include "sdl_deck.h"

void SDL_initdeck(Controller *ctrl, SDL_Cardmanager *sdl_cm) { // TODO: This should call the proper lock deck with path, and init the sdl texture arrays, etc.. after
    // TEMP INIT OF DECK 
        const char *msg;
        ctrl->model->deck = LoadDeck("", &msg);
        DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_STARTSIZE);
    //  

    for (int a = 0; a < NUM_COLUMNS; a++) {
        ll_node_card *curcard = ctrl->model->yukon->columnFront[a];
        while (curcard != NULL) {
            int index = getCardAbsoluteIndex(&curcard->card);
            sdl_cm->cardRects[index] = NULL;
            sdl_cm->cardRefs[index] = curcard;
            curcard = curcard->next;
        }
    } 

}