#include "sdlinit.h"

int sdl_view_init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL, %s\n", SDL_GetError());
        return 0;
    }
    printf("SDL initialized!\n");

    /* Create a window */
    SDL_Window *wind = SDL_CreateWindow("Hello Platformer!",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      WIDTH, HEIGHT, 0);

    if (!wind)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    mainloop(wind);

    SDL_DestroyWindow(wind);
    SDL_Quit();
    return 1;

}


int mainloop(SDL_Window *wind) { // taken from https://www.matsson.com/prog/platformer.c
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(wind, -1, render_flags);
    if (!rend)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(wind);
        SDL_Quit();
        return 0;
    }


    bool running = true;
    int x_prog = 0;
    while (running) {
        /* Clear screen */
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);
        /* Draw the rectangle */
        SDL_Rect rect = {(int) x_prog, (int) HEIGHT/2, 50, 50};
        x_prog = (x_prog + 1) % WIDTH;


        SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
        SDL_RenderFillRect(rend, &rect);
        /* Draw to window and loop */
        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS);
    }
}