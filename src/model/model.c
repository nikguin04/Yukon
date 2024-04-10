#include "model.h"



void initModel(Model *model) {
    model->intlist = NULL;
    model->yukon = (YukonStructure*) malloc(sizeof(YukonStructure));
    
    model->OPTION_IGNORE_HIDDEN = false;

    /*model->intlist = (ll_node_int*) malloc(sizeof(ll_node_int));
    model->intlist->val = 12345;
    model->intlist->next = NULL;*/
    //model->intlist = &list;
}

