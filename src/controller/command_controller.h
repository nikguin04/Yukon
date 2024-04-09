#ifndef cmd_controller_h
#define cmd_controller_h
#include "controller.h"

//typedef void (*CommandFunction)(Controller*, char*);

void LoadDeckAtPath(Controller *ctrl, char* path);
void LoadDeckWithInput(Controller *ctrl, char* input);

void ShowDeck(Controller *ctrl, char* input);

#endif