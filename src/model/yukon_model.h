#ifndef YUKON_MODEL_H
#define YUKON_MODEL_H

#include "linkedlist.h"

#define NUM_COLUMNS 7
#define NUM_FOUNDATIONS 4
static const int COLUMN_STARTSIZE[7] = {1, 6, 7, 8, 9, 10, 11};
static const int COLUMN_LOADSIZE[7] = {8, 8, 8, 7, 7, 7, 7};

typedef struct yukonStruct {
	ll_node_card *columnFront[NUM_COLUMNS];
	ll_node_card *foundationPile[NUM_FOUNDATIONS];
	bool play_phase;
} YukonStructure;

void DeckToYukon(ll_node_card *deck, YukonStructure *yukon, const int *columnHeightArray);

ll_node_card *DuplicateCardNode(ll_node_card *card, bool hidden);
void ClearGame(YukonStructure *yukon);
void ExposeYukonCards(YukonStructure *yukon, int amountToExpose, const int *columnHeightArray);

#endif
