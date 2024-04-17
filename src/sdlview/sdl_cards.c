#include "sdl_cards.h"
#include "deck.h"
#include <SDL_main.h>
#include <SDL_render.h>
#include <stdlib.h>



void Cards_GetEvent(SDLManager *manager, SDL_Event *event) {
    printf("Got event in cards: %d", event->type);
} 


void initCard_Textures(SDL_Surface *gScreenSurface, SDL_Renderer *rend) {
    card_texturebuffer = (SDL_Texture**) malloc(sizeof(SDL_Texture*) * DECK_LENGTH);
    for (int i = 0; i < DECK_LENGTH; i++) {
        char cardstr[3];
        char path[64];
        cardToString(&defaultDeck[i], cardstr);
        sprintf(path, "resource\\ModernCards\\%s.png", cardstr);
        card_texturebuffer[i] = LoadOptimizedImage(path, gScreenSurface, rend);
    }
    
}
