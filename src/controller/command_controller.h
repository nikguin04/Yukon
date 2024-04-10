#ifndef cmd_controller_h
#define cmd_controller_h
#include "controller.h"

//typedef void (*CommandFunction)(Controller*, char*);

char* LoadDeckAtPath(Controller *ctrl, char* path);

char* ShowDeck(Controller *ctrl, char* input);

#endif