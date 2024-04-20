#ifndef SDLINIT_H
#define SDLINIT_H

#include <stdio.h>
#include "sdlmanager.h"
#include "sdl_cards.h"
#include "sdl_deck.h"
#include "sdl_fps_counter.h"
#include "sdl_image_loader.h"
#include "sdl_command_parser.h"
#include "sdltext.h"
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_video.h>
#include "../controller/controller.h"
#include "../controller/command_controller.h"

#define WIDTH 1600
#define HEIGHT 900

#define FPS 120

#include "sdltext.h"

int sdl_view_init(Controller *ctrl);

#endif
