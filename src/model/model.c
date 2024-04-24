#include "model.h"
#include "yukon_model.h"

void initModel(Model *model) {
	model->deck = NULL;
	model->optionIgnoreHidden = false;

	model->yukon = (YukonStructure *) malloc(sizeof(YukonStructure));
	model->yukon->activeMove.card = NULL;
	model->yukon->play_phase = false;

	// Initialise all the yukon pointers to NULL
	for (int i = 0; i < NUM_COLUMNS; i++) { model->yukon->columnFront[i] = NULL; }
	for (int i = 0; i < NUM_FOUNDATIONS; i++) { model->yukon->foundationPile[i] = NULL; }
}
