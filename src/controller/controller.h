#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"

struct ControlStucture {
	Model *model;
	int val;
};
typedef struct ControlStucture Controller;

void initController(Controller *ctrlptr, Model *modelptr);
void addIntToModelArray(Controller *ctrl, int *intptr);

#endif
