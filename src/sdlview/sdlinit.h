#ifndef SDLINIT_H
#define SDLINIT_H

#include <stdio.h>
#include "sdlmanager.h"
#include "sdl_cards.h"
#include "sdl_deck.h"
#include "sdl_fps_counter.h"
#include "sdl_image_loader.h"
#include "sdl_command_parser.h"
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_video.h>
#include "../controller/controller.h"
#include "../controller/command_controller.h"

#define FPS 120

extern int WIDTH, HEIGHT;
extern int cardWidth, cardHeight, cardGap;

int sdl_view_init(Controller *ctrl);

void RenderMsgText(struct nk_context *ctx, const char *messageText, struct nk_font *messageFont);

#endif
