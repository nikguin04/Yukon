#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"
#include "../model/move.h"

enum COMMAND_TYPE {
	LOAD,
	SAVE,
	SHOW,
	SHUFFLEI,
	SHUFFLER,
	QQ,
	Q,
	PLAY
};

typedef struct ControlStructure {
	Model *model;
	enum COMMAND_TYPE last_command;
} Controller;

void initController(Controller *ctrl, Model *model);

const char *PerformMove(Controller *ctrl, Move move);

void GrabCard(Controller *ctrl, int source, float y, float height);
const char *ValidateMove(Controller *ctrl, int destination, MoveDestination *result);
void CancelMove(Controller *ctrl);
void CompleteMove(Controller *ctrl, MoveDestination dest);

#endif
