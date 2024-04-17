#ifndef SDLinit_h
#define SDLinit_h

#include "stdio.h"
//#include "SDL.h"
#include "sdlmanager.h"
#include "sdl_cards.h"
#include "sdl_fps_counter.h"
#include "sdl_image_loader.h"
#include "sdltext.h"
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <stdio.h>

#define WIDTH 640
#define HEIGHT 480
#define FPS 120



#include "sdltext.h"

int sdl_view_init();
int mainloop(SDLManager *manager);

#endif