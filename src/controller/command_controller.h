#ifndef COMMAND_CONTROLLER_H
#define COMMAND_CONTROLLER_H

#include "controller.h"

//typedef void (*CommandFunction)(Controller *, char *);

char *LoadDeckAtPath(Controller *ctrl, char *path);

char *ShowDeck(Controller *ctrl, char *input);

#endif
