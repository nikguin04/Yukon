#ifndef COMMAND_CONTROLLER_H
#define COMMAND_CONTROLLER_H

#include "controller.h"

char *LoadDeckFromFile(Controller *ctrl, char *path);
char *SaveDeckToFile(Controller *ctrl, char *path);
char *ShowDeck(Controller *ctrl, char *input);
char *ShuffleInterleaving(Controller *ctrl, char *split);
char *ShuffleRandom(Controller *ctrl, char *split);
char *QuitAndExit(Controller *ctrl, char *split);

#endif
