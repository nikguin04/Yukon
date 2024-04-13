#include "command_controller.h"
#include "yukon_model.h"
#include <cardShuffler.h>
#include <stdio.h>
#include <stdlib.h>

const char *LoadDeckFromFile(Controller *ctrl, char *path) {
	const char *msg;
	ctrl->model->deck = LoadDeck(path, &msg);
	DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_LOADSIZE);
	return msg;
}

const char *SaveDeckToFile(Controller *ctrl, char *path) {
	const char *msg;
	SaveDeck(ctrl->model->deck, path, &msg);
	return msg;
}

const char *ShowDeck(Controller *ctrl, char *_) {
	printf("Showing deck to user!\n");
	ctrl->model->optionIgnoreHidden = true;
	return "Showed deck to user!";
}

const char *ShuffleInterleaving(Controller *ctrl, char *split) {
	const char *msg;
	if (split == NULL) {
		ctrl->model->deck = shuffleInterleaving(ctrl->model->deck, 2, &msg, true);
		DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_LOADSIZE);
		return msg;
	} else {
		ctrl->model->deck = shuffleInterleaving(ctrl->model->deck, atoi(split), &msg, false);
		DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_LOADSIZE);
		return msg;
	}
}

const char *ShuffleRandom(Controller *ctrl, char *split) {
	ctrl->model->deck = shuffleRandom(ctrl->model->deck);
	DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_LOADSIZE);
	return "Deck randomly shuffled";
}

const char *QuitAndExit(Controller *_c, char *_i) {
	printf("Exiting game\n");
	exit(1);
}

const char *QuitGame(Controller *ctrl, char *_) {
    if (ctrl->model->yukon->play_phase) {
        ctrl->model->yukon->play_phase = false;
        ClearGame(ctrl->model->yukon);
        return "Game quit successfully";
    } else {
        return "Cannot quit game while not playing";
    }
    
}

const char *PlayGame(Controller *ctrl, char *_) {
    if (!ctrl->model->yukon->play_phase) {
        if (ctrl->model->deck) {
            ctrl->model->yukon->play_phase = true;
            DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_STARTSIZE);
            ExposeYukonCards(ctrl->model->yukon, 5, COLUMN_STARTSIZE);
            return "Game play started successfully";
        } else {
            return "Cannot start game with an empty deck!";
        }
    } else {
        return "Cannot play game while already playing!";
    }
}
