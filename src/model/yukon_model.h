#ifndef YUKON_MODEL_H
#define YUKON_MODEL_H

#include "linkedlist.h"

#define COLUMN_SIZE 7
static const int COLUMN_STARTSIZE[7] = {1, 6, 7, 8, 9, 10, 11};
static const int COLUMN_LOADSIZE[7] = {8, 8, 8, 7, 7, 7, 7};
#define FOUNDATION_SIZE 4

typedef struct yukonStruct {
	ll_node_card *columnFront[COLUMN_SIZE];

	ll_node_card *foundationPile[FOUNDATION_SIZE];
	bool play_phase;
} YukonStructure;

void DeckToYukon(ll_node_card *deck, YukonStructure *yukon, const int *columnHeightArray);
void YukonToDeck(ll_node_card *deck, YukonStructure *yukon);

ll_node_card *DuplicateCardNode(ll_node_card *card, bool hidden);
void ClearGame(YukonStructure *yukon);
void ExposeYukonCards(YukonStructure *yukon, const int amt_to_expose, const int *columnHeightArray);

#endif
