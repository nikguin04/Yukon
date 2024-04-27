#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"
#include "../model/move.h"

typedef struct ControlStructure {
	Model *model;
} Controller;

void initController(Controller *ctrl, Model *model);

const char *PerformMove(Controller *ctrl, Move move);

bool CheckWin(Controller *ctrl);

#endif
