#include "model.h"


int addToLinkedList(int *intptr) {

}

void initModel(Model *model) {
    //model.intlist = NULL;
    ll_node_int list;
    list.val = 12345;
    list.next = NULL;
    model->intlist = &list;
    return model;
}

