#include "sdlinit.h"
#include "nuklear.h"
#include "nuklear/nuklear_sdl_renderer.h"
#include "sdl_cards.h"
#include "yukon_model.h"

#define NK_ASSERT

int WIDTH, HEIGHT;
int cardWidth, cardHeight, cardGap;

int sdl_view_init(Controller *ctrl) {

	SDL_Window *win;
	SDL_Renderer *renderer;
	bool running = true;
	int flags = 0;
	float font_scale;

	int moveX, moveY;

	/* GUI */
	struct nk_context *ctx;
	struct nk_colorf bg;

	/* SDL setup */
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
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

	char SI_input_buffer[256] = "";
	char LD_input_buffer[256] = "";
	char SD_input_buffer[256] = "";
	const char *messageText = "";

	while (running) {
		SDL_GetWindowSize(win, &WIDTH, &HEIGHT);
		cardHeight = HEIGHT * 0.175f;
		cardWidth = cardHeight * sdl_cm.cardAspectRatio;
		cardGap = cardHeight * 0.25f;
		int cardMargin = cardWidth * 0.5f;
		int foundationX = cardMargin + (NUM_COLUMNS + 1) * cardWidth + (NUM_COLUMNS - 1) * (cardGap / 2);

		YukonStructure *yukon = ctrl->model->yukon;

		/* Input */
		SDL_Event evt;
		nk_input_begin(ctx);
		while (SDL_PollEvent(&evt)) {
			if (evt.type == SDL_QUIT) goto cleanup;
			nk_sdl_handle_event(&evt);
			if (evt.type != (yukon->activeMove.card == NULL ? SDL_MOUSEBUTTONDOWN : SDL_MOUSEBUTTONUP)) continue;
			if (evt.button.button != SDL_BUTTON_LEFT || !yukon->play_phase) continue;
			int x = evt.button.x, y = evt.button.y;
			int place = 0;
			int cardX = 0, cardY = cardGap + 73;
			float columnY = 0, columnHeight = 0;
			y -= cardY;
			if (y >= 0) {
				x -= cardMargin;
				int cardSpacing = cardWidth + cardGap / 2;
				if (x >= 0 && x < NUM_COLUMNS * cardSpacing && x % cardSpacing < cardWidth) {
					x /= cardSpacing;
					place = x + 1;
					columnY = (float) y / (float) cardGap;
					columnHeight = (float) cardHeight / (float) cardGap;
					cardX = x * cardSpacing + cardMargin;
				}
				x -= foundationX - cardMargin;
				cardSpacing = cardHeight + cardGap / 2;
				if (x >= 0 && x < cardWidth && y < NUM_FOUNDATIONS * cardSpacing && y % cardSpacing < cardHeight) {
					y /= cardSpacing;
					place = -(y + 1);
					cardX = foundationX;
					cardY += y * cardSpacing;
				}
			}
			if (yukon->activeMove.card == NULL) {
				if (place == 0) continue;
				int ret = GrabCard(ctrl, place, columnY, columnHeight);
				if (place > 0) cardY += ret * cardGap;
				moveX = evt.button.x - cardX;
				moveY = evt.button.y - cardY;
			} else {
				MoveDestination moveDest;
				messageText = ValidateMove(ctrl, place, &moveDest);
				if (moveDest.destPointer != NULL) {
					CompleteMove(ctrl, moveDest);
					if (CheckWin(ctrl)) messageText = "YOU WIN!";
				} else {
					CancelMove(ctrl);
				}
			}
		}
		nk_sdl_handle_grab(); /* optional grabbing behavior */
		nk_input_end(ctx);

		/* GUI */
		if (nk_begin(ctx, "Yukon Solitaire", nk_rect(0, 0, WIDTH, HEIGHT), 0)) {

			RenderMsgText(ctx, messageText, messageFont);
			//nkRenderFoundationPiles(ctx, ctrl, &sdl_cm);

			nk_layout_row_dynamic(ctx, 3, 1); // General top gap so everything is not completely at the top
			nk_spacing(ctx, 1);

			// Add command buttons
			nk_layout_row_static(ctx, 30, 100, 8);
			if (!ctrl->model->yukon->play_phase) {
				if (nk_button_label(ctx, "Load")) {
					messageText = LoadDeckFromFile(ctrl, parseCommand(LD_input_buffer));
				}
				if (nk_button_label(ctx, "Save")) {
					messageText = SaveDeckToFile(ctrl, parseCommand(SD_input_buffer));
				}
				if (nk_button_label(ctx, "Interleave Shuffle")) {
					messageText = ShuffleInterleaving(ctrl, parseCommand(SI_input_buffer));
				}
				if (nk_button_label(ctx, "Random Shuffle")) {
					messageText = ShuffleRandom(ctrl, NULL);
				}
				if (nk_button_label(ctx, "Show Cards")) {
					messageText = ShowDeck(ctrl, NULL);
				}
				if (nk_button_label(ctx, "Play")) {
					messageText = PlayGame(ctrl, NULL);
				}
			} else {
				if (nk_button_label(ctx, "Quit")) {
					messageText = QuitGame(ctrl, NULL);
				}
			}

			if (nk_button_label(ctx, "Quit And Exit")) {
				messageText = QuitAndExit(ctrl, NULL);
			}

			// Add input boxes for command buttons
			nk_layout_row_static(ctx, 30, 100, 3);
			if (!ctrl->model->yukon->play_phase) {
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, LD_input_buffer, 256, nk_filter_default);
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, SD_input_buffer, 256, nk_filter_default);
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, SI_input_buffer, 256, nk_filter_default);
			}

			//nkRenderCardColumns(ctrl, ctx, &sdl_cm);
		}
		nk_end(ctx);

		SDL_SetRenderDrawColor(renderer, bg.r * 255, bg.g * 255, bg.b * 255, bg.a * 255);
		SDL_RenderClear(renderer);

		nk_sdl_render(NK_ANTI_ALIASING_ON);

		// Set option to ignore false if command is not show
		if (ctrl->last_command != SHOW && ctrl->model->optionIgnoreHidden) { ctrl->model->optionIgnoreHidden = false; }
		RenderCardColumns(renderer, ctrl, &sdl_cm, cardMargin, cardGap + 73);

		if (ctrl->model->yukon->play_phase)
			RenderFoundationPiles(renderer, ctrl, &sdl_cm, foundationX, cardGap + 73);

		if (ctrl->model->yukon->activeMove.card != NULL) {
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			RenderCardColumn(renderer, ctrl, &sdl_cm, ctrl->model->yukon->activeMove.card, mouseX - moveX, mouseY - moveY);
		}

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
