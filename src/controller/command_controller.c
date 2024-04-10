#include "command_controller.h"

char *LoadDeckAtPath(Controller *ctrl, char *path) {
	char *msg;
	ctrl->model->deck = LoadDeck(path, &msg);
	DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_LOADSIZE);
	return msg;
}

char *ShowDeck(Controller *ctrl, char *_) {
	printf("Showing deck to user!\n");
	ctrl->model->optionIgnoreHidden = true;
	return "Showed deck to user!";
}
