#ifndef YUKON_MODEL_H
#define YUKON_MODEL_H

#include "linkedlist.h"

#define COLUMN_SIZE 7
static const int COLUMN_STARTSIZE[7] = {1, 6, 7, 8, 9, 10, 11};
static const int COLUMN_LOADSIZE[7] = {8, 8, 8, 7, 7, 7, 7};

typedef struct yukonStruct {
	ll_node_card *Column_FRONT[COLUMN_SIZE];

	int foundation_CLUBS;
	int foundation_DIAMONDS;
	int foundation_HEARTS;
	int foundation_SPADES;
} YukonStructure;

void DeckToYukon(ll_node_card *deck, YukonStructure *yukon, const int *Column_Height_Array);
void YukonToDeck(ll_node_card *deck, YukonStructure *yukon);

ll_node_card *DuplicateCardNode(ll_node_card *card, bool hidden);

#endif
