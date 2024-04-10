#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include "yukon_model.h"
#include "linkedlist.h"

typedef struct ModelStructure {
	ll_node_int *intlist;
	ll_node_card *deck;
	YukonStructure *yukon;
	bool optionIgnoreHidden;
} Model;

void initModel(Model *model);

#endif
