#ifndef controller_h
#define controller_h
#include "../model/model.h"
#include "command_controller.h"

struct ControlStucture { // linked list node
    Model *model;
    int val;
};
typedef struct ControlStucture Controller;


void initController(Controller *ctrlptr, Model *modelptr);
void addIntToModelArray(Controller *ctrl, int *intptr);

//void LoadDeckAtPath(Controller *ctrl, char* path);

#endif