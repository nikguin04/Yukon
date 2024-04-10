#include "model.h"

void initModel(Model *model) {
	model->intlist = NULL;
	model->yukon = (YukonStructure *) malloc(sizeof(YukonStructure));
	model->yukon->Column_FRONT[0] = NULL;

	model->OPTION_IGNORE_HIDDEN = false;
}
