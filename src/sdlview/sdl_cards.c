#include <SDL_main.h>
#include <SDL_render.h>
#include "sdl_cards.h"
#include "sdl_image_loader.h"
#include "sdlinit.h"

void InitCardTextures(SDL_CardManager *cardManager, SDL_Renderer *renderer) {
	cardManager->placeholder_texture = LoadSDLImage("resource/Card-Placeholder.png", renderer);
	cardManager->back_texture = LoadSDLImage("resource/Backs/Card-Back-04.png", renderer);
	int w, h;
	SDL_QueryTexture(cardManager->back_texture, NULL, NULL, &w, &h);
	cardManager->cardAspectRatio = (float) w / (float) h;
	for (int i = 0; i < DECK_LENGTH; i++) {
		char cardstr[3];
		char path[64];
		CardToString(defaultDeck[i], cardstr);
		sprintf(path, "resource/ModernCards/%s.png", cardstr);
		SDL_Texture *texture = LoadSDLImage(path, renderer);
		cardManager->card_textures[i] = texture;
	}
}

void RenderCardColumns(SDL_Renderer *renderer, Controller *ctrl, SDL_CardManager *cardManager, int x, int y) {
	for (int i = 0; i < NUM_COLUMNS; i++) {
		ll_node_card *card = ctrl->model->yukon->columnFront[i];
		RenderCardColumn(renderer, ctrl, cardManager, card, x + (cardWidth + cardGap / 2) * i, y);
	}
}

void RenderCardColumn(SDL_Renderer *renderer, Controller *ctrl, SDL_CardManager *cardManager, ll_node_card *card, int x, int y) {
	if (card == NULL) {
		SDL_Rect cardRect = {x, y, cardWidth, cardHeight};
		SDL_RenderCopy(renderer, cardManager->placeholder_texture, NULL, &cardRect);
		return;
	}
	int i = 0;
	while (card != NULL) {
		int cardIndex = GetCardAbsoluteIndex(card->card);
		SDL_Texture *tex = !card->hidden || ctrl->model->optionIgnoreHidden ? cardManager->card_textures[cardIndex] : cardManager->back_texture;
		SDL_Rect cardRect = {x, y + cardGap * i, cardWidth, cardHeight};
		SDL_RenderCopy(renderer, tex, NULL, &cardRect);
		i++;
		card = card->next;
	}
}

void RenderFoundationPiles(SDL_Renderer *renderer, Controller *ctrl, SDL_CardManager *cardManager, int x, int y) {
	for (int i = 0; i < NUM_FOUNDATIONS; i++) {
		ll_node_card *card = ctrl->model->yukon->foundationPile[i];
		SDL_Texture *tex = card == NULL ? cardManager->placeholder_texture :
			(!card->hidden || ctrl->model->optionIgnoreHidden
				? cardManager->card_textures[GetCardAbsoluteIndex(card->card)]
				: cardManager->back_texture);
		SDL_Rect cardRect = {x, y + (cardHeight + cardGap / 2) * i, cardWidth, cardHeight};
		SDL_RenderCopy(renderer, tex, NULL, &cardRect);
	}
}

void nkRenderCardColumns(Controller *ctrl, struct nk_context *ctx, SDL_CardManager *cardManager) {
	const int yNegativeGap = 50;
	ll_node_card *cur[NUM_COLUMNS];
	for (int i = 0; i < NUM_COLUMNS; i++) {
		cur[i] = ctrl->model->yukon->columnFront[i];
	}
	bool all_cur_done = false;
	while (!all_cur_done) {
		all_cur_done = true;

		nk_layout_row_static(ctx, 140, 100, NUM_COLUMNS); // SIZE IS NOT CORRECT!
		for (int i = 0; i < NUM_COLUMNS; i++) {
			if (cur[i] != NULL) {
				all_cur_done = false;
				int index = GetCardAbsoluteIndex(cur[i]->card);

				// Ternary operator to show card only if it is not hidden or hidden is ignored, else, show back texture
				struct nk_image nki = (!cur[i]->hidden || ctrl->model->optionIgnoreHidden) ? nk_image_ptr(cardManager->card_textures[index]) : nk_image_ptr(cardManager->back_texture);
				struct nk_rect img_bounds = nk_widget_bounds(ctx);
				cardManager->cardRects[index] = img_bounds;
				nk_image(ctx, nki);
				cur[i] = cur[i]->next;
			} else {
				// FILL RECT HERE!
				nk_spacing(ctx, 1);
			}
		}

		nk_layout_row_dynamic(ctx, -yNegativeGap, 1);
		nk_spacing(ctx, 1);
	}
	nk_layout_row_dynamic(ctx, yNegativeGap, 1); // Cancel out the last gap
	nk_spacing(ctx, 1);
}

void nkRenderFoundationPiles(struct nk_context *ctx, Controller *ctrl, SDL_CardManager *sdl_cm) {
	int offsetHeight = 30 + 3 + 30 + 3 + 3 + 3 + 3 + 1;
	int cardHeight = HEIGHT / 45 * 7;
	nk_layout_row_static(ctx, offsetHeight, 1, 1); // Adjust text to bottom

	for (int i = 0; i < NUM_FOUNDATIONS; i++) {
		nk_layout_row_static(ctx, cardHeight, HEIGHT / 9, NUM_COLUMNS + 2);
		nk_spacing(ctx, NUM_COLUMNS + 1);

		struct nk_image nki
			= ctrl->model->yukon->foundationPile[i] != NULL
			  ? nk_image_ptr(sdl_cm->card_textures[GetCardAbsoluteIndex(ctrl->model->yukon->foundationPile[i]->card)])
			  : nk_image_ptr(sdl_cm->back_texture);
		struct nk_rect img_bounds = nk_widget_bounds(ctx); // Use this later for grabbing
		nk_image(ctx, nki);
	}
	nk_layout_row_dynamic(ctx, (-offsetHeight - (cardHeight * 4)) / 2 - (3 * 5), 1); // Cancel out the gap (this works like shit when scaling resolution up)
	nk_spacing(ctx, 1);
}
