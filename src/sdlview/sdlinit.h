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

#define WIDTH 1600
#define HEIGHT 900

#define FPS 120

int sdl_view_init(Controller *ctrl);

void renderMsgText(struct nk_context *ctx, const char *message_text, struct nk_font *messageFont);
void renderFoundationPile(struct nk_context *ctx, Controller *ctrl, SDL_Cardmanager *sdl_cm);

#endif
