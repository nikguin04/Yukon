#ifndef controller_h
#define controller_h
#include "../model/model.h"

typedef struct ControlStucture { // linked list node
    Model *model;
    int val;
} Controller;


Controller initController();
void addIntToModelArray(Controller *ctrl, int *intptr);

#endif