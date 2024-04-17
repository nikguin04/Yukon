#include "sdl_cards.h"


void Cards_GetEvent(SDLManager *manager, SDL_Event *event) {
    printf("Got event in cards: %d", event->type);
} 


void initCard_Textures(SDL_Surface *gScreenSurface, SDL_Renderer *rend) {

    char path[] = "resource\\ModernCards\\AC.png";
    card_textures[0] = LoadOptimizedImage(path, gScreenSurface, rend);
}
