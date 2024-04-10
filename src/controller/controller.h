#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"

typedef struct ControlStructure {
	Model *model;
	int val;
} Controller;

void initController(Controller *ctrl, Model *model);
void addIntToModelArray(Controller *ctrl, int *intptr);

#endif
