#include "command_controller.h"
#include <cardShuffler.h>
#include <stdlib.h>

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

char *ShuffleInterleaving(Controller *ctrl, char *split) {
    char *msg;
    if (split == NULL) {
        ctrl->model->deck = shuffleInterleaving(ctrl->model->deck, 2, &msg, true);
        DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_LOADSIZE);
        return msg;
    }
    else {
        ctrl->model->deck = shuffleInterleaving(ctrl->model->deck, atoi(split), &msg, false);
        DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_LOADSIZE);
        return msg;
    }
}

char *ShuffleRandom(Controller *ctrl, char *split) {
    ctrl->model->deck = shuffleRandom(ctrl->model->deck);
    DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_LOADSIZE);
    return "Deck randomly shuffled";
}