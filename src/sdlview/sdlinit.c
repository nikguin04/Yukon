#include "sdlinit.h"

int sdl_view_init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL, %s\n", SDL_GetError());
        return 0;
    }
    printf("SDL initialized!\n");

    GUIManager manager;

    /* Create a window */
    manager.wind = SDL_CreateWindow("Hello Platformer!",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      WIDTH, HEIGHT, 0);

    if (!manager.wind)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    if (TTF_Init()==-1) {
        printf("Failed to initialize TTF: %s", SDL_GetError());
        return 1;
    }

    manager.font = TTF_OpenFont("resource/aptos.ttf", 32);
    if (manager.font==NULL){
        printf("Failed to load font: %s", SDL_GetError());
    }


    mainloop(&manager);

    SDL_DestroyWindow(manager.wind);	
    IMG_Quit();
    SDL_Quit();
    return 1;

}


int mainloop(GUIManager *manager) { // taken from https://www.matsson.com/prog/platformer.c
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(manager->wind, -1, render_flags);
    SDL_Event event;
    if (!rend)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(manager->wind);
        SDL_Quit();
        return 0;
    }


    bool running = true;
    int x_prog = 0;
    while (running) {
        /* Clear screen */
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);
        // Draw the rectangle 
        SDL_Rect rect = {(int) x_prog, (int) HEIGHT/2, 200, 200};
        x_prog = (x_prog + 1) % WIDTH;


        /*SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
        SDL_RenderFillRect(rend, &rect);*/

        SDL_Surface* gScreenSurface = NULL;
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
            return 0;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( manager->wind );
        }
        char path[] = "resource\\DEMONS.png";

        SDL_Surface* loadedSurface = IMG_Load( path );
        if( loadedSurface == NULL )
        {
            printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
            return 0;
        }

        SDL_Surface* optimizedSurface = NULL;
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
            return 0;
        }
        SDL_FreeSurface( loadedSurface );

        SDL_Texture * texture = SDL_CreateTextureFromSurface(rend, optimizedSurface);
        //SDL_Rect rect = {(int) WIDTH/2 - 200/2, (int) HEIGHT/2 - 200/2, 200, 200};
        SDL_RenderCopy(rend, texture, NULL, &rect);

        sdltexttest(manager);
        SDL_Rect textrect = {50, (int) HEIGHT/4, 400, 100};
        SDL_Color textcol = {100, 200, 255, 255};
        SDL_Surface *surface = TTF_RenderText_Solid(manager->font, manager->statusmsg, textcol);
        SDL_Texture *texttexture = SDL_CreateTextureFromSurface(rend, surface);
        SDL_RenderCopy(rend, texttexture, NULL, &textrect);

        SDL_FreeSurface(surface);
        //SDL_DestroyTexture(texture);

        /* Draw to window and loop */
        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS);

        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
            case SDL_QUIT:
                break;
        }
    }
}