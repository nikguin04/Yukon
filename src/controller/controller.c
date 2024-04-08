#include "controller.h"



void addIntToModelArray(Controller *ctrl, int *intptr) {
    appendToEnd(&ctrl->model->intlist, *intptr);
}

void initController(Controller *ctrlptr, Model *modelptr) {
    ctrlptr->model = modelptr;
    ctrlptr->val = 0;
}
void LoadDeckAtPath(char* path) {
    ll_node_card* deck = LoadDeck(path);
}