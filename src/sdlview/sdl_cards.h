#ifndef sdl_cards_h
#define sdl_cards_h

#include <SDL_rect.h>
#include <SDL_render.h>
#include "linkedlist.h"
#include "sdlmanager.h"
#include <SDL_events.h>
#include "../model/deck.h"
#include "sdl_image_loader.h"
#include <SDL_render.h>
#include <SDL_surface.h>
#include "deck.h"
#include <stdio.h> 
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


void Cards_GetEvent(SDLManager *manager, SDL_Event *event);

typedef struct SDL_Cardmanager_struct {
    SDL_Texture *card_textures[DECK_LENGTH];
    ll_node_card *cardRefs[DECK_LENGTH];
    struct nk_rect cardRects[DECK_LENGTH];
} SDL_Cardmanager;

void initCard_Textures(SDL_Cardmanager *cardmanager, SDL_Renderer *rend);

void SDL_cards_render(SDL_Renderer *rend, Controller *ctrl, SDL_Cardmanager *cardmanager);

struct nk_rect* getCardRect(YukonStructure *yukon, int column, int ll_index);

struct nk_context;
void RenderCardColumns(Controller *ctrl, struct nk_context *ctx, SDL_Cardmanager *sdl_cm);

//ll_node_card* GetHoveredCard(Controller *ctrl, , struct nk_vec2 mouse_pos);

#endif