#include "sdl_deck.h"
#include "linkedlist.h"

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
            struct nk_rect nkr = {0,0,0,0};
            sdl_cm->cardRects[index] = nkr;
            sdl_cm->cardRefs[index] = curcard;
            curcard = curcard->next;
        }
    } 

}

void CheckCardHover(Controller *ctrl, struct nk_input *nk_inp, SDL_Cardmanager *sdl_cm) {
    for (int a = 0; a < NUM_COLUMNS; a++) {
        ll_node_card *curcard = ctrl->model->yukon->columnFront[a];
        ll_node_card *hover = NULL;
        while (curcard != NULL) {
            int index = getCardAbsoluteIndex(&curcard->card);
            
            if (nk_input_is_mouse_hovering_rect(nk_inp, sdl_cm->cardRects[index])) {
                hover = curcard; // this will loop to last card in column
            }

            curcard = curcard->next;
        }
        if (hover) {
            char cardstr[8];
            CardToString(hover->card, cardstr);
            printf("Mouse is hovering over the card: %s\n", cardstr);
            break; 
        }
    } 
}