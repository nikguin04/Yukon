#ifndef SDLinit_h
#define SDLinit_h

#include "stdio.h"
//#include "SDL.h"
#include "sdlmanager.h"

#define WIDTH 640
#define HEIGHT 480
#define FPS 120



#include "sdltext.h"

int sdl_view_init();
int mainloop(SDLManager *manager);

#endif