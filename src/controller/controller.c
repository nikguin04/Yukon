#include "controller.h"

void addIntToModelArray(Controller *ctrl, int *intptr) {
	appendToEnd(&ctrl->model->intlist, *intptr);
}

void initController(Controller *ctrl, Model *model) {
	ctrl->model = model;
	ctrl->val = 0;
}
