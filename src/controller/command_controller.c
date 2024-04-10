#include "command_controller.h"

char* LoadDeckAtPath(Controller *ctrl, char* path) {
    ctrl->model->deck = LoadDeck(path);
    DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_LOADSIZE);
    return "Loaded deck successfully!";
}


char* ShowDeck(Controller *ctrl, char* _) {
    printf("showing deck to user!\n");
    return "Showed deck to user!";
}