#include "sdlinit.h"
#include "nuklear.h"
#include "nuklear/nuklear_sdl_renderer.h"
#include "sdl_cards.h"
#include "yukon_model.h"

#define NK_ASSERT

int WIDTH, HEIGHT;

int sdl_view_init(Controller *ctrl) {

	SDL_Window *win;
	SDL_Renderer *renderer;
	bool running = true;
	int flags = 0;
	float font_scale;

	/* GUI */
	struct nk_context *ctx;
	struct nk_colorf bg;

	/* SDL setup */
	SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
	SDL_Init(SDL_INIT_VIDEO);

	win = SDL_CreateWindow("Yukon Solitaire",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900,
		SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);

	if (win == NULL) {
		SDL_Log("Error SDL_CreateWindow %s", SDL_GetError());
		exit(-1);
	}

	flags |= SDL_RENDERER_ACCELERATED;
	flags |= SDL_RENDERER_PRESENTVSYNC;

	renderer = SDL_CreateRenderer(win, -1, flags);

	if (renderer == NULL) {
		SDL_Log("Error SDL_CreateRenderer %s", SDL_GetError());
		exit(-1);
	}

	/* scale the renderer output for High-DPI displays */
	{
		int render_w, render_h;
		float scale_x, scale_y;
		SDL_GetRendererOutputSize(renderer, &render_w, &render_h);
		SDL_GetWindowSize(win, &WIDTH, &HEIGHT);
		scale_x = (float) (render_w) / (float) (WIDTH);
		scale_y = (float) (render_h) / (float) (HEIGHT);
		SDL_RenderSetScale(renderer, scale_x, scale_y);
		font_scale = scale_y;
	}

	/* GUI */
	ctx = nk_sdl_init(win, renderer);
	/* Load Fonts: if none of these are loaded a default font will be used  */
	/* Load Cursor: if you uncomment cursor loading please hide the cursor */

	struct nk_font_atlas *atlas;
	struct nk_font_config config = nk_font_config(0);
	struct nk_font *font;
	struct nk_font *messageFont;

	/* set up the font atlas and add desired font; note that font sizes are
	 * multiplied by font_scale to produce better results at higher DPIs */
	nk_sdl_font_stash_begin(&atlas);
	font = nk_font_atlas_add_from_file(atlas, "resource/aptos.ttf", 14 * font_scale, &config);
	messageFont = nk_font_atlas_add_from_file(atlas, "resource/aptos.ttf", 30 * font_scale, &config);
	nk_sdl_font_stash_end();

	/* this hack makes the font appear to be scaled down to the desired
	 * size and is only necessary when font_scale > 1 */
	font->handle.height /= font_scale;
	nk_style_set_font(ctx, &font->handle);

	bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;

	SDL_CardManager sdl_cm;
	InitCardTextures(&sdl_cm, renderer);
	SDL_initdeck(ctrl, &sdl_cm);

	char SI_input_buffer[256] = "";
	char LD_input_buffer[256] = "";
	char SD_input_buffer[256] = "";
	const char *message_text = "";

	while (running) {
		SDL_GetWindowSize(win, &WIDTH, &HEIGHT);
		/* Input */
		SDL_Event evt;
		nk_input_begin(ctx);
		while (SDL_PollEvent(&evt)) { // make this a switch case??
			if (evt.type == SDL_QUIT) goto cleanup;
			nk_sdl_handle_event(&evt);
			if (evt.type == SDL_MOUSEBUTTONDOWN || evt.type == SDL_MOUSEBUTTONUP) {
				CardEventHandler(&evt, ctrl, &ctx->input, &sdl_cm);
			}
		}
		nk_sdl_handle_grab(); /* optional grabbing behavior */
		nk_input_end(ctx);

		/* GUI */
		if (nk_begin(ctx, "Yukon Solitaire", nk_rect(0, 0, WIDTH, HEIGHT), 0)) {

			RenderMsgText(ctx, message_text, messageFont);
			RenderFoundationPiles(ctx, ctrl, &sdl_cm);

			nk_layout_row_dynamic(ctx, 3, 1); // General top gap so everything is not completely at the top
			nk_spacing(ctx, 1);

			// Add command buttons
			nk_layout_row_static(ctx, 30, 100, 8);
			if (!ctrl->model->yukon->play_phase) {
				if (nk_button_label(ctx, "Load")) {
					message_text = LoadDeckFromFile(ctrl, parseCommand(LD_input_buffer));
				}
				if (nk_button_label(ctx, "Save")) {
					message_text = SaveDeckToFile(ctrl, parseCommand(SD_input_buffer));
				}
				if (nk_button_label(ctx, "Interleave Shuffle")) {
					message_text = ShuffleInterleaving(ctrl, parseCommand(SI_input_buffer));
				}
				if (nk_button_label(ctx, "Random Shuffle")) {
					message_text = ShuffleRandom(ctrl, NULL);
				}
				if (nk_button_label(ctx, "Show Cards")) {
					message_text = ShowDeck(ctrl, NULL);
				}
				if (nk_button_label(ctx, "Play")) {
					message_text = PlayGame(ctrl, NULL);
				}
			} else {
				if (nk_button_label(ctx, "Quit")) {
					message_text = QuitGame(ctrl, NULL);
				}
			}

			if (nk_button_label(ctx, "Quit And Exit")) {
				message_text = QuitAndExit(ctrl, NULL);
			}

			// Add input boxes for command buttons
			nk_layout_row_static(ctx, 30, 100, 3);
			if (!ctrl->model->yukon->play_phase) {
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, LD_input_buffer, 256, nk_filter_default);
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, SD_input_buffer, 256, nk_filter_default);
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, SI_input_buffer, 256, nk_filter_default);
			}

			RenderCardColumns(ctrl, ctx, &sdl_cm);
		}
		nk_end(ctx);

		SDL_SetRenderDrawColor(renderer, bg.r * 255, bg.g * 255, bg.b * 255, bg.a * 255);
		SDL_RenderClear(renderer);

		nk_sdl_render(NK_ANTI_ALIASING_ON);

		SDL_RenderPresent(renderer);
	}

	cleanup:
	nk_sdl_shutdown();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}

void RenderMsgText(struct nk_context *ctx, const char *messageText, struct nk_font *messageFont) {
	nk_layout_row_dynamic(ctx, HEIGHT / 2 - 25, 1); // Adjust text to bottom
	nk_spacing(ctx, 1);

	// Display message from commands
	nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
	nk_style_push_font(ctx, &messageFont->handle);
	nk_layout_row_push(ctx, 105);
	nk_label(ctx, "Message: ", NK_TEXT_LEFT);
	nk_layout_row_push(ctx, 650);
	nk_label(ctx, messageText, NK_TEXT_LEFT);
	nk_style_pop_font(ctx);
	nk_layout_row_end(ctx);

	nk_layout_row_dynamic(ctx, -(HEIGHT / 2 - 25) - 30, 1); // Cancel out the gap
	nk_spacing(ctx, 1);
}

void RenderFoundationPiles(struct nk_context *ctx, Controller *ctrl, SDL_CardManager *sdl_cm) {
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
        sdl_cm->foundationRects[i] = img_bounds;
		nk_image(ctx, nki);
	}
	nk_layout_row_dynamic(ctx, (-offsetHeight - (cardHeight * 4)) / 2 - (3 * 5), 1); // Cancel out the gap (this works like shit when scaling resolution up)
	nk_spacing(ctx, 1);
}
