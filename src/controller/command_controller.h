#ifndef COMMAND_CONTROLLER_H
#define COMMAND_CONTROLLER_H

#include "deck.h"
#include "controller.h"


const char *LoadDeckFromFile(Controller *ctrl, char *path);
const char *SaveDeckToFile(Controller *ctrl, char *path);
const char *ShowDeck(Controller *ctrl, char *input);
const char *ShuffleInterleaving(Controller *ctrl, char *split);
const char *ShuffleRandom(Controller *ctrl, char *split);
const char *QuitAndExit(Controller *ctrl, char *split);

#endif
