#include "model.h"
#include "yukon_model.h"

void initModel(Model *model) {
	model->yukon = (YukonStructure *) malloc(sizeof(YukonStructure));
	model->yukon->columnFront[0] = NULL;
	for (int i = 0; i < FOUNDATION_SIZE; i++) {model->yukon->foundationPile[i] = NULL;} // init foundations to null

	model->optionIgnoreHidden = false;
}
