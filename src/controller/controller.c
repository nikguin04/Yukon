#include "controller.h"



void addIntToModelArray(Controller *ctrl, int *intptr) {
    ctrl->val = ctrl->val + *intptr;
}

Controller initController() {
    Controller ctrl;
    ctrl.val = 0;
    return ctrl;
}