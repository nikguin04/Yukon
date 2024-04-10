#ifndef model_h
#define model_h
#include <stdio.h>
//#include "../controller/controller.h"
#include "yukon_model.h"
#include "linkedlist.h"

struct ModelStucture { // linked list node
    ll_node_int *intlist;
    ll_node_card *deck;
    YukonStructure *yukon;
    bool OPTION_IGNORE_HIDDEN;
};
typedef struct ModelStucture Model;

void initModel(Model *model);
#endif

