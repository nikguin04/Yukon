#include "model.h"
#include "yukon_model.h"

void initModel(Model *model) {
	model->deck = NULL;
	model->yukon = (YukonStructure *) malloc(sizeof(YukonStructure));
	ClearGame(model->yukon);

	model->optionIgnoreHidden = false;
	model->yukon->play_phase = false;
}
