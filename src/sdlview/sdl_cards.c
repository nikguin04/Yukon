#include <SDL_main.h>
#include <SDL_render.h>
#include "sdl_cards.h"
#include "sdl_image_loader.h"
#include "sdlinit.h"

void initCard_Textures(SDL_Cardmanager *cardmanager, SDL_Renderer *rend) {
	cardmanager->back_texture = LoadSDLImage("resource\\Backs\\Card-Back-04.png", rend);
	for (int i = 0; i < DECK_LENGTH; i++) {
		char cardstr[3];
		char path[64];
		CardToString(defaultDeck[i], cardstr);
		sprintf(path, "resource\\ModernCards\\%s.png", cardstr);
		SDL_Texture *texture = LoadSDLImage(path, rend);
		cardmanager->card_textures[i] = texture;
	}
}

void SDL_cards_render(SDL_Renderer *rend, Controller *ctrl, SDL_Cardmanager *cardmanager) {
	// Change all the sizes and gaps later, size is 768x1063
	float xSize = 0.10;
	float ySize = 0.1384;
	float xGap = 0.12;
	float yGap = 0.04;

	for (int a = 0; a < NUM_COLUMNS; a++) {
		ll_node_card *curcard = ctrl->model->yukon->columnFront[a];
		int b = 0;
		while (curcard != NULL) {
			int cardIndex = getCardAbsoluteIndex(&curcard->card);
			SDL_Texture *tex = cardmanager->card_textures[cardIndex];

			SDL_Rect cardrect = {WIDTH * xGap * (a + 1), WIDTH * yGap * (++b), WIDTH * xSize, WIDTH * ySize};
			SDL_RenderCopy(rend, tex, NULL, &cardrect);
			curcard = curcard->next;
		}
	}
}

void RenderCardColumns(Controller *ctrl, struct nk_context *ctx, SDL_Cardmanager *sdl_cm) {
	// Set option to ignore false if command is not show
	if (ctrl->last_command != SHOW && ctrl->model->optionIgnoreHidden) { ctrl->model->optionIgnoreHidden = false; }

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
			if (cur[i]) {
				all_cur_done = false;
				int index = getCardAbsoluteIndex(&cur[i]->card);

				// Ternary operator to show card only if it is not hidden or hidden is ignored, else, show back texture
				struct nk_image nki = (!cur[i]->hidden || ctrl->model->optionIgnoreHidden) ? nk_image_ptr(sdl_cm->card_textures[index]) : nk_image_ptr(sdl_cm->back_texture);
				struct nk_rect img_bounds = nk_widget_bounds(ctx);
				sdl_cm->cardRects[index] = img_bounds; // WARNING: This might be a memory leak
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
