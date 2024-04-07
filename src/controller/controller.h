#ifndef controller_h
#define controller_h
//#include "../model/model.h"

struct ControlStucture { // linked list node
    //Model *model;
    int val;
};
typedef struct ControlStucture Controller;


Controller initController();
void addIntToModelArray(Controller *ctrl, int *intptr);

#endif