#ifndef SDLinit_h
#define SDLinit_h

#include "stdio.h"
#include "SDL.h"
#include "SDL_image.h"

#define WIDTH 640
#define HEIGHT 480
#define FPS 1


int sdl_view_init();
int mainloop(SDL_Window *wind);

#endif