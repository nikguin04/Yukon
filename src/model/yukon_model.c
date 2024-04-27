#include "yukon_model.h"
#include "linkedlist.h"

void DeckToYukon(ll_node_card *deck, YukonStructure *yukon, const int *columnHeightArray) { // Puts the deck into column structure according to yukon rules
	ClearGame(yukon); // Avoid memory leaks by clearing any previous stuff
	ll_node_card *columnTail[NUM_COLUMNS];
	ll_node_card *deckIndex = deck;
	if (!deckIndex) {
		printf("Exiting due to nulled deck passed to DeckToYukon()\n");
		exit(0);
	}
	for (int i = 0; i < NUM_COLUMNS; i++) {
		yukon->columnFront[i] = DuplicateCardNode(deckIndex, true);
		columnTail[i] = yukon->columnFront[i];
		deckIndex = deckIndex->next;
	} // Height = 1

	int height = 0;
	bool atEnd = false;
	while (!atEnd) {
		height++;
		atEnd = true;
		for (int i = 0; i < NUM_COLUMNS; i++) {
			if (columnHeightArray[i] > height) {
				atEnd = false;
				columnTail[i]->next = DuplicateCardNode(deckIndex, true);
				columnTail[i] = columnTail[i]->next;
				deckIndex = deckIndex->next;
			}
		}
	}

	for (int i = 0; i < NUM_FOUNDATIONS; i++) {
		yukon->foundationPile[i] = NULL;
	}
}

void ExposeYukonCards(YukonStructure *yukon, int amountToExpose, const int *columnHeightArray) {
	for (int i = 0; i < NUM_COLUMNS; i++) {
		ll_node_card *card = yukon->columnFront[i];
		for (int a = 0; a < columnHeightArray[i]; a++) {
			card->hidden = (columnHeightArray[i] - a > amountToExpose);
			card = card->next;
		}
	}
}

ll_node_card *DuplicateCardNode(ll_node_card *card, bool hidden) {
	ll_node_card *newCard = (ll_node_card *) malloc(sizeof(ll_node_card));
	newCard->card.value = card->card.value;
	newCard->card.suit = card->card.suit;
	newCard->hidden = hidden;
	newCard->next = NULL;
	return newCard;
}

void ClearGame(YukonStructure *yukon) {
	for (int i = 0; i < NUM_COLUMNS; i++) { freeList(&yukon->columnFront[i]); }
	for (int i = 0; i < NUM_FOUNDATIONS; i++) { freeList(&yukon->foundationPile[i]); }
	freeList(&yukon->activeMove.card);
}
