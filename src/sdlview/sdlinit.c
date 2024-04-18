#include "sdlinit.h"
#include "sdl_cards.h"
#include <SDL_render.h>
#include <SDL_video.h>
#include <stdio.h>

#include "nuklear/nuklear_sdl_renderer.h"
#include "sdl_image_loader.h"

/*#define NK_INTERNAL_H
#define NK_INCLUDE_FIXED_TYPES
#include "nuklear/nuklear_sdl_renderer.h"*/

int sdl_view_init(Controller *ctrl) {

    
    SDL_Window *win;
    SDL_Renderer *renderer;
    int running = 1;
    int flags = 0;
    float font_scale = 1;

    /* GUI */
    struct nk_context *ctx;
    struct nk_colorf bg;

    /* SDL setup */
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Demo",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);

    if (win == NULL) {
        SDL_Log("Error SDL_CreateWindow %s", SDL_GetError());
        exit(-1);
    }

    flags |= SDL_RENDERER_ACCELERATED;
    flags |= SDL_RENDERER_PRESENTVSYNC;

    renderer = SDL_CreateRenderer(win, -1, flags);

    if (renderer == NULL) {
        SDL_Log("Error SDL_CreateRenderer %s", SDL_GetError());
        exit(-1);
    }

    /* scale the renderer output for High-DPI displays */
    {
        int render_w, render_h;
        int window_w, window_h;
        float scale_x, scale_y;
        SDL_GetRendererOutputSize(renderer, &render_w, &render_h);
        SDL_GetWindowSize(win, &window_w, &window_h);
        scale_x = (float)(render_w) / (float)(window_w);
        scale_y = (float)(render_h) / (float)(window_h);
        SDL_RenderSetScale(renderer, scale_x, scale_y);
        font_scale = scale_y;
    }

    /* GUI */
    ctx = nk_sdl_init(win, renderer);
    /* Load Fonts: if none of these are loaded a default font will be used  */
    /* Load Cursor: if you uncomment cursor loading please hide the cursor */
    {
        struct nk_font_atlas *atlas;
        struct nk_font_config config = nk_font_config(0);
        struct nk_font *font;

        /* set up the font atlas and add desired font; note that font sizes are
         * multiplied by font_scale to produce better results at higher DPIs */
        nk_sdl_font_stash_begin(&atlas);
        font = nk_font_atlas_add_default(atlas, 13 * font_scale, &config);
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/DroidSans.ttf", 14 * font_scale, &config);*/
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 16 * font_scale, &config);*/
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13 * font_scale, &config);*/
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12 * font_scale, &config);*/
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10 * font_scale, &config);*/
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Cousine-Regular.ttf", 13 * font_scale, &config);*/
        nk_sdl_font_stash_end();

        /* this hack makes the font appear to be scaled down to the desired
         * size and is only necessary when font_scale > 1 */
        font->handle.height /= font_scale;
        /*nk_style_load_all_cursors(ctx, atlas->cursors);*/
        nk_style_set_font(ctx, &font->handle);
    }
    bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
    

    char path[] = "resource\\DEMONS.png";
    SDL_Texture *tex = LoadSDLImage(path, renderer);
    while (running)
    {
        /* Input */
        SDL_Event evt;
        nk_input_begin(ctx);
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) goto cleanup;
            nk_sdl_handle_event(&evt);
        }
        nk_sdl_handle_grab(); /* optional grabbing behavior */
        nk_input_end(ctx);

        /* GUI */
        if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            enum {EASY, HARD};
            static int op = EASY;
            static int property = 20;

            nk_layout_row_static(ctx, 30, 80, 1);
            if (nk_button_label(ctx, "button"))
                fprintf(stdout, "button pressed\n");
            nk_layout_row_dynamic(ctx, 30, 2);
            if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
            if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
            nk_layout_row_dynamic(ctx, 25, 1);
            nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label(ctx, "background:", NK_TEXT_LEFT);
            nk_layout_row_dynamic(ctx, 25, 1);
            if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx),400))) {
                nk_layout_row_dynamic(ctx, 120, 1);
                bg = nk_color_picker(ctx, bg, NK_RGBA);
                nk_layout_row_dynamic(ctx, 25, 1);
                bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f,0.005f);
                bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f,0.005f);
                bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f,0.005f);
                bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);
                nk_combo_end(ctx);
            }
            nk_layout_row_static(ctx, 100, 100, 1);
            struct nk_image nki;
            nki.handle.ptr = tex;
            nki.w = 100;
            nki.h = 100;
            nki.region[0] = 1;
            struct nk_rect imgr = {100,100,100,100};
            struct nk_command_buffer *nkcb;
            nkcb = nk_window_get_canvas(ctx);
            //nk_command_buffer_init(&nkcb, 0, 0);
            struct nk_color col;
            col.a = 255;
            col.g = 255;
            nk_draw_image(nkcb, imgr, &nki, col);
            //nk_image(ctx, nki);
            /*if (nk_button_image(ctx, nki)) {
                printf("IMAGE CLICKED!\n");
            }*/

            
            
            /*struct nk_image img;
            nk_image(ctx, img)
            if((struct nk_context *, struct nk_image img)) {
                printf("Image pressed");
            }*/
        }
        nk_end(ctx);

        /* -------------- EXAMPLES ---------------- */
        #ifdef INCLUDE_CALCULATOR
          calculator(ctx);
        #endif
        #ifdef INCLUDE_CANVAS
        canvas(ctx);
        #endif
        #ifdef INCLUDE_OVERVIEW
          overview(ctx);
        #endif
        #ifdef INCLUDE_NODE_EDITOR
          node_editor(ctx);
        #endif
        /* ----------------------------------------- */

        SDL_SetRenderDrawColor(renderer, bg.r * 255, bg.g * 255, bg.b * 255, bg.a * 255);
        SDL_RenderClear(renderer);

        nk_sdl_render(NK_ANTI_ALIASING_ON);

        SDL_RenderPresent(renderer);
    }

    cleanup:
        nk_sdl_shutdown();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 0;
}



/*int sdl_view_init(Controller *ctrl) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL, %s\n", SDL_GetError());
        return 0;
    }
    printf("SDL initialized!\n");

    SDLManager manager;

    // Create a window 
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

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(manager.wind, -1, render_flags);


    if (!rend)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(manager.wind);
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
        gScreenSurface = SDL_GetWindowSurface( manager.wind );
    }

    manager.font = TTF_OpenFont("resource/aptos.ttf", 32);
    if (manager.font==NULL){
        printf("Failed to load font: %s", SDL_GetError());
    }

    SDL_Cardmanager sdl_cm;
    initCard_Textures(&sdl_cm, gScreenSurface, rend);


    mainloop(ctrl, &manager, gScreenSurface, rend, &sdl_cm);

    SDL_DestroyWindow(manager.wind);	
    IMG_Quit();
    SDL_Quit();
    return 1;

}*/


int mainloop(Controller *ctrl, SDLManager *manager, SDL_Surface *gScreenSurface, SDL_Renderer *rend, SDL_Cardmanager *sdl_cm) { // taken from https://www.matsson.com/prog/platformer.c

    SDL_Event event;
    int mouseX=0, mouseY=0;
    EventObserver event_observers[EventObserverCount];


    char path[] = "resource\\DEMONS.png";
    manager->temptexture = LoadOptimizedImage(path, gScreenSurface, rend);

    sdltexttest("Hello, world!", manager);

    FpsCounterManager *fcm = InitFpsCounter(manager);

    
    const char *funcmsg; 
    funcmsg = LoadDeckFromFile(ctrl, ""); // INIT DECK TEMPORARY!

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

        SDL_cards_render(rend, ctrl, sdl_cm);
        

         // TODO: maybe do this at init?
        //SDL_Rect rect = {(int) WIDTH/2 - 200/2, (int) HEIGHT/2 - 200/2, 200, 200};
        SDL_RenderCopy(rend, manager->temptexture, NULL, &rect);
        
        // Get and render Mouse location TEXT
        SDL_GetMouseState(&mouseX, &mouseY);
        char printtext[32];
        sprintf(printtext, "Mouse: %d:%d", mouseX, mouseY);
        sdltexttest(printtext, manager);
        SDL_Color textcol = {100, 200, 255, 255};
        SDL_Surface *surface = TTF_RenderText_Solid(manager->font, manager->statusmsg, textcol);
        SDL_Rect textrect = {WIDTH-WIDTH/6, HEIGHT-WIDTH/100-surface->h, surface->w, surface->h}; // TODO: free all memory from here, or do all this at init
        SDL_Texture *texttexture = SDL_CreateTextureFromSurface(rend, surface);
        SDL_RenderCopy(rend, texttexture, NULL, &textrect);

        // RENDER FPS TEXT
        UpdateFpsCounter(fcm);
        SDL_Color fps_textcol = {20, 255, 20, 255};
        SDL_Surface *fps_surface = TTF_RenderText_Solid(manager->font, manager->fpstext, fps_textcol);
        SDL_Rect fps_textrect = {WIDTH/100, WIDTH/100, fps_surface->w, fps_surface->h}; // TODO: free all memory from here, or do all this at init
        SDL_Texture *fps_texttexture = SDL_CreateTextureFromSurface(rend, fps_surface);
        SDL_RenderCopy(rend, fps_texttexture, NULL, &fps_textrect);


        // RENDER Function message TETX
        SDL_Color fmsg_textcol = {100, 200, 255, 255};
        SDL_Surface *fmsg_surface = TTF_RenderText_Solid(manager->font, funcmsg, fmsg_textcol);
        SDL_Rect fmsg_textrect = {WIDTH/100, HEIGHT-WIDTH/100-fmsg_surface->h, fmsg_surface->w, fmsg_surface->h}; // TODO: free all memory from here, or do all this at init
        SDL_Texture *fmsg_texttexture = SDL_CreateTextureFromSurface(rend, fmsg_surface);
        SDL_RenderCopy(rend, fmsg_texttexture, NULL, &fmsg_textrect);



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
                    // DO SOMETHING WITH MOUSE BTN DOWN
                    break;
                case SDL_QUIT:
                    break;
            }   
        }
    }
}