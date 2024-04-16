#ifndef SDLinit_h
#define SDLinit_h

#include "stdio.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#define WIDTH 640
#define HEIGHT 480
#define FPS 120

typedef struct GUI_Struct_struct {
    SDL_Window *wind;
    TTF_Font* font;
    char* statusmsg;
} GUIManager;


int sdl_view_init();
int mainloop(GUIManager *manager);

#endif