#include "command_controller.h"

void LoadDeckAtPath(Controller *ctrl, char* path) {
    ctrl->model->deck = LoadDeck(path);
    DeckToYukon(ctrl->model->deck, ctrl->model->yukon, COLUMN_LOADSIZE);
}
void LoadDeckWithInput(Controller *ctrl, char* input) {
    printf("loading deck with input: %s", input);
}

void ShowDeck(Controller *ctrl, char* _) {
    printf("showing deck to user!");
}