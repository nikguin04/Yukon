#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include "yukon_model.h"
#include "linkedlist.h"

typedef struct ModelStucture {
	ll_node_int *intlist;
	ll_node_card *deck;
	YukonStructure *yukon;
	bool OPTION_IGNORE_HIDDEN;
} Model;

void initModel(Model *model);

#endif
