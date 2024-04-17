#include "sdl_cards.h"
#include "deck.h"
#include "linkedlist.h"
#include "sdlinit.h"
#include "yukon_model.h"
#include <SDL_main.h>
#include <SDL_render.h>
#include <stdlib.h>



void Cards_GetEvent(SDLManager *manager, SDL_Event *event) {
    printf("Got event in cards: %d", event->type);
} 


void initCard_Textures(SDL_Cardmanager *cardmanager, SDL_Surface *gScreenSurface, SDL_Renderer *rend) {
    //card_texturebuffer = (SDL_Texture**) malloc(sizeof(SDL_Texture*) * DECK_LENGTH);
    for (int i = 0; i < DECK_LENGTH; i++) {
        char cardstr[3];
        char path[64];
        cardToString(&defaultDeck[i], cardstr);
        sprintf(path, "resource\\ModernCards\\%s.png", cardstr);
        SDL_Texture *texture = LoadOptimizedImage(path, gScreenSurface, rend);
        cardmanager->card_textures[i] = texture;
    }
    
}

void SDL_cards_render(SDL_Renderer *rend, Controller *ctrl, SDL_Cardmanager *cardmanager) {
    float xSize = 0.12;// changge all the sizes and gaps later
    float ySize = 0.16;  
    float xGap = 0.15;
    float yGap = 0.05;

    for (int a = 0; a < COLUMN_SIZE; a++) {
        ll_node_card *curcard = ctrl->model->yukon->columnFront[a];
        int b = 0;
        while (curcard != NULL) {
            int cardIndex = getCardAbsoluteIndex(&curcard->card);
            SDL_Texture *tex = cardmanager->card_textures[cardIndex];

            SDL_Rect cardrect = {WIDTH*xGap*(a+1), WIDTH*yGap*(++b), WIDTH*xSize, HEIGHT*ySize}; 
            SDL_RenderCopy(rend, tex, NULL, &cardrect);
            curcard = curcard->next;
        }
    } 

}
