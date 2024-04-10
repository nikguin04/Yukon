#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"

typedef struct ControlStructure {
	Model *model;
} Controller;

void initController(Controller *ctrl, Model *model);

#endif
