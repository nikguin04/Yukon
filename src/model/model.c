#include "model.h"

void initModel(Model *model) {
	model->intlist = NULL;
	model->yukon = (YukonStructure *) malloc(sizeof(YukonStructure));
	model->yukon->columnFront[0] = NULL;

	model->optionIgnoreHidden = false;
}
