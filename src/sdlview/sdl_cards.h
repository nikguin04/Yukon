#ifndef SDL_CARDS_H
#define SDL_CARDS_H

#include <stdio.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_events.h>
#include "sdlmanager.h"
#include "sdl_image_loader.h"
#include "../model/deck.h"
#include "../model/linkedlist.h"
#include "../model/yukon_model.h"
#include "../controller/controller.h"

#define NK_ASSERT
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_SDL_RENDERER_IMPLEMENTATION
#include "nuklear/nuklear.h"

typedef struct SDL_CardManager_struct {
	SDL_Texture *back_texture;
	SDL_Texture *card_textures[DECK_LENGTH];
	ll_node_card *cardRefs[DECK_LENGTH];
	struct nk_rect cardRects[DECK_LENGTH];
} SDL_CardManager;

void InitCardTextures(SDL_CardManager *cardManager, SDL_Renderer *renderer);

void SDL_cards_render(SDL_Renderer *renderer, Controller *ctrl, SDL_CardManager *cardManager);

void RenderCardColumns(Controller *ctrl, struct nk_context *ctx, SDL_CardManager *sdl_cm);

#endif
