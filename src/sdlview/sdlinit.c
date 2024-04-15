#include "sdlinit.h"

void sdl_view_init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL, %s\n", SDL_GetError());
        return;
    }
    printf("SDL initialized!\n");



    SDL_Quit();

}