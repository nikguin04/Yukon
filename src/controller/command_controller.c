#include "command_controller.h"

char *LoadDeckFromFile(Controller *ctrl, char *path) {
	char *msg;
	ctrl->model->deck = LoadDeck(path, &msg);
	DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_LOADSIZE);
	return msg;
}

char *SaveDeckToFile(Controller *ctrl, char *path) {
	char *msg;
	SaveDeck(ctrl->model->deck, path, &msg);
	return msg;
}

char *ShowDeck(Controller *ctrl, char *_) {
	printf("Showing deck to user!\n");
	ctrl->model->optionIgnoreHidden = true;
	return "Showed deck to user!";
}
