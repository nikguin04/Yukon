#ifndef cmd_controller_h
#define cmd_controller_h
#include "controller.h"

//typedef void (*CommandFunction)(Controller*, char*);

void LoadDeckAtPath(Controller *ctrl, char* path);
void LoadDeckWithInput(Controller *ctrl, char* input);

void ShowDeck(Controller *ctrl, char* input);

typedef void (*CommandFunction)(Controller*, char*);
typedef struct commandStruct { // linked list node
    char *input;
    bool takes_input;
    char *friendly_name;
    CommandFunction function;
} Command;

#define COMMAND_COUNT 2
Command commands[COMMAND_COUNT+1] = {
 {'LD', true, 'Load', LoadDeckWithInput},
 {'SW', false, 'Show', ShowDeck}
};

#endif