#include "command_controller.h"
#include "yukon_model.h"
#include <cardShuffler.h>
#include <stdio.h>
#include <stdlib.h>

const char *LoadDeckFromFile(Controller *ctrl, char *path) {
	if (ctrl->model->yukon->play_phase)
		return "Cannot load a deck while playing game";
	const char *msg;
	ctrl->model->deck = LoadDeck(path, &msg);
	DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_LOADSIZE);
	return msg;
}

const char *SaveDeckToFile(Controller *ctrl, char *path) {
	if (ctrl->model->yukon->play_phase)
		return "Cannot save a deck while playing game";
	const char *msg;
	SaveDeck(ctrl->model->deck, path, &msg);
	return msg;
}

const char *ShowDeck(Controller *ctrl, char *_) {
	if (ctrl->model->yukon->play_phase)
		return "Cannot show deck while playing";
	printf("Showing deck to user!\n");
	ctrl->model->optionIgnoreHidden = true;
	return "Showed deck to user!";
}

const char *ShuffleInterleaving(Controller *ctrl, char *split) {
	if (ctrl->model->yukon->play_phase)
		return "Cannot shuffle deck interleaving while playing";
	const char *msg;
	if (split == NULL) {
		ctrl->model->deck = shuffleInterleaving(ctrl->model->deck, 2, &msg, true);
	} else {
		ctrl->model->deck = shuffleInterleaving(ctrl->model->deck, atoi(split), &msg, false);
	}
	DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_LOADSIZE);
	return msg;
}

const char *ShuffleRandom(Controller *ctrl, char *split) {
	if (ctrl->model->yukon->play_phase)
		return "Cannot shuffle deck at random while playing";
	ctrl->model->deck = shuffleRandom(ctrl->model->deck);
	DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_LOADSIZE);
	return "Deck randomly shuffled";
}

const char *QuitAndExit(Controller *_c, char *_i) {
	printf("Exiting game\n");
	exit(1);
}

const char *QuitGame(Controller *ctrl, char *_) {
	if (!ctrl->model->yukon->play_phase)
		return "Cannot quit game while not playing";
	ctrl->model->yukon->play_phase = false;
	ClearGame(ctrl->model->yukon);
	return "Game quit successfully";
}

const char *PlayGame(Controller *ctrl, char *_) {
	if (ctrl->model->yukon->play_phase)
		return "Cannot play game while already playing!";
	if (ctrl->model->deck == NULL)
		return "Cannot start game with an empty deck!";
	ctrl->model->yukon->play_phase = true;
	DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_STARTSIZE);
	ExposeYukonCards(ctrl->model->yukon, 5, COLUMN_STARTSIZE);
	return "Game play started successfully";
}
