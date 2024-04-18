#include "sdl_cards.h"
#include "deck.h"
#include "linkedlist.h"

#include "sdl_image_loader.h"
#include "sdlinit.h"
#include "yukon_model.h"
#include <SDL_main.h>
#include <SDL_render.h>
#include <stdlib.h>






void Cards_GetEvent(SDLManager *manager, SDL_Event *event) {
    printf("Got event in cards: %d", event->type);
} 


void initCard_Textures(SDL_Cardmanager *cardmanager, SDL_Renderer *rend) {
    //card_texturebuffer = (SDL_Texture**) malloc(sizeof(SDL_Texture*) * DECK_LENGTH);
    for (int i = 0; i < DECK_LENGTH; i++) {
        char cardstr[3];
        char path[64];
        CardToString(defaultDeck[i], cardstr);
        sprintf(path, "resource\\ModernCards\\%s.png", cardstr);
        SDL_Texture *texture = LoadSDLImage(path, rend);
        cardmanager->card_textures[i] = texture;
    }
    
}

void SDL_cards_render(SDL_Renderer *rend, Controller *ctrl, SDL_Cardmanager *cardmanager) {
    float xSize = 0.10;// changge all the sizes and gaps later, size is 768x1063
    float ySize = 0.1384;  
    float xGap = 0.12;
    float yGap = 0.04;

    for (int a = 0; a < NUM_COLUMNS; a++) {
        ll_node_card *curcard = ctrl->model->yukon->columnFront[a];
        int b = 0;
        while (curcard != NULL) {
            int cardIndex = getCardAbsoluteIndex(&curcard->card);
            SDL_Texture *tex = cardmanager->card_textures[cardIndex];

            SDL_Rect cardrect = {WIDTH*xGap*(a+1), WIDTH*yGap*(++b), WIDTH*xSize, WIDTH*ySize}; 
            SDL_RenderCopy(rend, tex, NULL, &cardrect);
            curcard = curcard->next;
        }
    } 

}

struct nk_rect* getCardRect(YukonStructure *yukon, int column, int ll_index) {
    return NULL;
}


void RenderCardColumns(Controller *ctrl, struct nk_context *ctx, SDL_Cardmanager *sdl_cm) {
    const int yNegativeGap = 50;
            ll_node_card *cur[NUM_COLUMNS];
            for (int i = 0; i < NUM_COLUMNS; i++) {
                cur[i] = ctrl->model->yukon->columnFront[i];
            }
            bool all_cur_done = false;
            while (!all_cur_done) {
                all_cur_done = true;
                
                nk_layout_row_static(ctx, 140, 100, NUM_COLUMNS); // SIZE IS NOT CORRECT!
                for (int i = 0; i < NUM_COLUMNS; i++) {
                    if (cur[i]) {
                        all_cur_done = false;
                        int index = getCardAbsoluteIndex(&cur[i]->card);
                        struct nk_image nki = nk_image_ptr(sdl_cm->card_textures[index]);
                        struct nk_rect img_bounds = nk_widget_bounds(ctx);
                        sdl_cm->cardRects[index] = img_bounds; // WARNING: This might be a memory leak
                        //printf("h:%f, w:%f, x:%f, y:%f\n", img_bounds.h, img_bounds.w, img_bounds.x, img_bounds.y); // TEMP BOUND PRINT
                        if (nk_button_image(ctx, nki)) {
                            char dbgstr[10];
                            CardToString(cur[i]->card, dbgstr);
                            printf("Button image clicked: %s\n", dbgstr);
                        }
                        cur[i] = cur[i]->next;
                    } else {
                        // FILL RECT HERE!
                        nk_spacing(ctx, 1);
                    }
                }
                nk_layout_row_dynamic(ctx, -yNegativeGap, 1);
                nk_spacing(ctx, 1); 
            }
            nk_layout_row_dynamic(ctx, yNegativeGap, 1); // Cancel out the last gap
            nk_spacing(ctx, 1); 
}