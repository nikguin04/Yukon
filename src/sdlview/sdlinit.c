#include "sdlinit.h"
#include "sdl_cards.h"
#include <SDL_video.h>


int sdl_view_init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL, %s\n", SDL_GetError());
        return 0;
    }
    printf("SDL initialized!\n");

    SDLManager manager;

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


int mainloop(SDLManager *manager) { // taken from https://www.matsson.com/prog/platformer.c
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(manager->wind, -1, render_flags);
    SDL_Event event;
    int mouseX=0, mouseY=0;
    if (!rend)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(manager->wind);
        SDL_Quit();
        return 0;
    }

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

    EventObserver event_observers[EventObserverCount];


    char path[] = "resource\\DEMONS.png";
    manager->temptexture = LoadOptimizedImage(path, gScreenSurface, rend);
    SDL_Cardmanager sdl_cm;
    initCard_Textures(&sdl_cm, gScreenSurface, rend);
    sdltexttest("Hello, world!", manager);

    FpsCounterManager *fcm = InitFpsCounter(manager);

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

        
        

         // TODO: maybe do this at init?
        //SDL_Rect rect = {(int) WIDTH/2 - 200/2, (int) HEIGHT/2 - 200/2, 200, 200};
        SDL_RenderCopy(rend, manager->temptexture, NULL, &rect);
        
        // RENDER MOUSE LOCATION TEXT
        SDL_Rect textrect = {50, (int) HEIGHT/4, 400, 100}; // TODO: free all memory from here, or do all this at init
        SDL_Color textcol = {100, 200, 255, 255};
        SDL_Surface *surface = TTF_RenderText_Solid(manager->font, manager->statusmsg, textcol);
        SDL_Texture *texttexture = SDL_CreateTextureFromSurface(rend, surface);
        SDL_RenderCopy(rend, texttexture, NULL, &textrect);

        // RENDER FPS TEXT
        UpdateFpsCounter(fcm);
        SDL_Rect fps_textrect = {50, 50, 250, 75}; // TODO: free all memory from here, or do all this at init
        SDL_Color fps_textcol = {20, 255, 20, 255};
        SDL_Surface *fps_surface = TTF_RenderText_Solid(manager->font, manager->fpstext, fps_textcol);
        SDL_Texture *fps_texttexture = SDL_CreateTextureFromSurface(rend, fps_surface);
        SDL_RenderCopy(rend, fps_texttexture, NULL, &fps_textrect);

        // RENDER TEST FOR CARD IMAGES
        SDL_Rect cardtestrect = {800, 200, 150, 208};
        SDL_RenderCopy(rend, sdl_cm.card_textures[5], NULL, &cardtestrect);

        /* Draw to window and loop */
        SDL_RenderPresent(rend);

        // Render then free/destroy
        SDL_FreeSurface(surface);
        //SDL_DestroyTexture(texture);
        SDL_DestroyTexture(texttexture);
        SDL_FreeSurface(fps_surface);
        SDL_DestroyTexture(fps_texttexture);

        SDL_Delay(1000/FPS);

        //SDL_WaitEvent(&event);
        
        if (SDL_PollEvent(&event)) {
            switch (event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouseX, &mouseY);
                    char printtext[32];
                    sprintf(printtext, "Mouse: %d:%d", mouseX, mouseY);
                    sdltexttest(printtext, manager);
                    break;
                case SDL_QUIT:
                    break;
            }   
        }
    }
}