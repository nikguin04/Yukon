#ifndef model_h
#define model_h
#include <stdio.h>
//#include "../controller/controller.h"
#include "linkedlist.h"

struct ModelStucture { // linked list node
    ll_node_int *intlist;
    ll_node_card *deck;
};
typedef struct ModelStucture Model;

int addToLinkedList(int *intptr);

void initModel(Model *model);
#endif

