#include "controller.h"



void addIntToModelArray(Controller *ctrl, int *intptr) {
    appendToEnd(&ctrl->model->intlist, *intptr);
}

Controller initController(Model *modelptr) {
    Controller ctrl;
    ctrl.model = modelptr;
    ctrl.val = 0;
    return ctrl;
}