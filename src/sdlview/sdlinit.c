#include "sdlinit.h"
#include "nuklear/nuklear_sdl_renderer.h"

#define NK_ASSERT

//#define NK_INTERNAL_H
//#define NK_INCLUDE_FIXED_TYPES
//#include "nuklear/nuklear_sdl_renderer.h"

int sdl_view_init(Controller *ctrl) {

	SDL_Window *win;
	SDL_Renderer *renderer;
	int running = 1;
	int flags = 0;
	float font_scale = 1;

	/* GUI */
	struct nk_context *ctx;
	struct nk_colorf bg;

	/* SDL setup */
	SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
	SDL_Init(SDL_INIT_VIDEO);

	win = SDL_CreateWindow("Yukon Solitaire",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

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
		int window_w, window_h;
		float scale_x, scale_y;
		SDL_GetRendererOutputSize(renderer, &render_w, &render_h);
		SDL_GetWindowSize(win, &window_w, &window_h);
		scale_x = (float) (render_w) / (float) (window_w);
		scale_y = (float) (render_h) / (float) (window_h);
		SDL_RenderSetScale(renderer, scale_x, scale_y);
		font_scale = scale_y;
	}

	/* GUI */
	ctx = nk_sdl_init(win, renderer);
	/* Load Fonts: if none of these are loaded a default font will be used  */
	/* Load Cursor: if you uncomment cursor loading please hide the cursor */
	{
		struct nk_font_atlas *atlas;
		struct nk_font_config config = nk_font_config(0);
		struct nk_font *font;

		/* set up the font atlas and add desired font; note that font sizes are
		 * multiplied by font_scale to produce better results at higher DPIs */
		nk_sdl_font_stash_begin(&atlas);
		//font = nk_font_atlas_add_default(atlas, 13 * font_scale, &config);
		font = nk_font_atlas_add_from_file(atlas, "resource/aptos.ttf", 14 * font_scale, &config);
		nk_sdl_font_stash_end();

		/* this hack makes the font appear to be scaled down to the desired
		 * size and is only necessary when font_scale > 1 */
		font->handle.height /= font_scale;
		/*nk_style_load_all_cursors(ctx, atlas->cursors);*/
		nk_style_set_font(ctx, &font->handle);
	}
	bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;

	SDL_Cardmanager sdl_cm;
	initCard_Textures(&sdl_cm, renderer);
	SDL_initdeck(ctrl, &sdl_cm);

	char SI_input_buffer[256] = "";
	char LD_input_buffer[256] = "";
	char SD_input_buffer[256] = "";
	const char *message_text = "";

	while (running) {
//		if (strcmp(SI_input_buffer, "") == 0) {
//			SI_input_buffer = NULL;
//		}

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
		if (nk_begin(ctx, "Yukon Solitaire", nk_rect(50, 50, 230, 250),
			NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
			NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)
		) {
//			enum { EASY, HARD };
//			static int op = EASY;
//			static int property = 20;

//			nk_layout_row_dynamic(ctx, 25, 1);
//			nk_layout_row_dynamic(ctx, 30, 1);
//			nk_label(ctx, "Input", NK_TEXT_LEFT);
//			nk_edit_string(ctx, NK_EDIT_FIELD, input_buffer, &input_buffer_length, 256, nk_filter_default);
//			input_buffer_length = strlen(input_buffer);

//			nk_layout_row_dynamic(ctx, 30, 2);
//			if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
//			if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
//			nk_layout_row_dynamic(ctx, 25, 1);
//			nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

//			nk_layout_row_dynamic(ctx, 20, 1);
//			nk_label(ctx, "background:", NK_TEXT_LEFT);
//			nk_layout_row_dynamic(ctx, 25, 1);
//			if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx), 400))) {
//				nk_layout_row_dynamic(ctx, 120, 1);
//				bg = nk_color_picker(ctx, bg, NK_RGBA);
//				nk_layout_row_dynamic(ctx, 25, 1);
//				bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f, 0.005f);
//				bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f, 0.005f);
//				bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f, 0.005f);
//				bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f, 0.005f);
//				nk_combo_end(ctx);
//			}

			// Add command buttons
			nk_layout_row_static(ctx, 30, 80, 8);
			if (nk_button_label(ctx, "LD")) {
				message_text = LoadDeckFromFile(ctrl, parseCommand(LD_input_buffer));
			}

			if (nk_button_label(ctx, "SD")) {
				message_text = SaveDeckToFile(ctrl, parseCommand(SD_input_buffer));
			}
			if (nk_button_label(ctx, "SI")) {
				message_text = ShuffleInterleaving(ctrl, parseCommand(SI_input_buffer));
			}
			if (nk_button_label(ctx, "SR")) {
				message_text = ShuffleRandom(ctrl, NULL);
			}
			if (nk_button_label(ctx, "SW")) {
				message_text = ShowDeck(ctrl, NULL);
			}
			if (nk_button_label(ctx, "P")) {
				message_text = PlayGame(ctrl, NULL);
			}
			if (nk_button_label(ctx, "Q")) {
				message_text = QuitGame(ctrl, NULL);
			}
			if (nk_button_label(ctx, "QQ")) {
				message_text = QuitAndExit(ctrl, NULL);
			}

            // Add input boxes
            nk_layout_row_static(ctx, 30, 80, 3);
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, LD_input_buffer, 256, nk_filter_default);
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, SD_input_buffer, 256, nk_filter_default);
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, SI_input_buffer, 256, nk_filter_default);

			RenderCardColumns(ctrl, ctx, &sdl_cm);
			//CheckCardHover(ctrl, &ctx->input, &sdl_cm);

			// Display message from commands
            nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
//            nk_style_set_font(ctx, &messageFont->handle);
            nk_layout_row_push(ctx, 50);
            nk_label(ctx, "Message: ", NK_TEXT_LEFT);
            nk_layout_row_push(ctx, 500);
            nk_label(ctx, message_text, NK_TEXT_LEFT);

            nk_layout_row_end(ctx);

//			const float item_widths[] = {50, 500};
//			nk_layout_row_static(ctx, 30, 80, 2);
//			nk_layout_row(ctx, NK_STATIC, 30, 2, item_widths);
//			nk_label(ctx, "Message: ", NK_TEXT_LEFT);
//			nk_label(ctx, message_text, NK_TEXT_LEFT);


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
