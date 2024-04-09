#include "controller.h"



void addIntToModelArray(Controller *ctrl, int *intptr) {
    appendToEnd(&ctrl->model->intlist, *intptr);
}

void initController(Controller *ctrlptr, Model *modelptr) {
    ctrlptr->model = modelptr;
    ctrlptr->val = 0;
}
void LoadDeckAtPath(Controller *ctrl, char* path) {
    ctrl->model->deck = LoadDeck(path);
}