#include "yukon_model.h"
#include "linkedlist.h"

/*void YukonToDeck(ll_node_card *deck, YukonStructure *yukon) { // Puts columns into a deck again // DO NOT USE, NOT IN GAME RULES!
	deck = yukon->columnFront[0];
	ll_node_card *movingdeck = deck;
	yukon->columnFront[0] = NULL;
	for (int i = 1; i < COLUMN_SIZE; i++) {
		movingdeck->next = yukon->columnFront[i];
		yukon->columnFront[i] = NULL;
		while (movingdeck->next != NULL) { movingdeck = movingdeck->next; }
	}
}*/ // deprecated function

void DeckToYukon(ll_node_card *deck, YukonStructure *yukon, const int *columnHeightArray) { // Puts the deck into column structure according to yukon rules
	ll_node_card *columnTail[COLUMN_SIZE];
	ll_node_card *deckindex = deck;
	if (!deckindex) {
		printf("Exiting due to nulled deck passed to DeckToYukon()\n");
		exit(0);
	}
	for (int i = 0; i < COLUMN_SIZE; i++) {
		yukon->columnFront[i] = DuplicateCardNode(deckindex, true);
		columnTail[i] = yukon->columnFront[i];
		deckindex = deckindex->next;
	} // Height = 1

	int height = 0;
	bool atend = false;
	while (!atend) {
		height++;
		atend = true;
		for (int i = 0; i < COLUMN_SIZE; i++) {
			if (columnHeightArray[i] > height) {
				atend = false;
				columnTail[i]->next = DuplicateCardNode(deckindex, true);
				columnTail[i] = columnTail[i]->next;
				deckindex = deckindex->next;
			}
		}
	}

	for (int i = 0; i < FOUNDATION_SIZE; i++) {
		yukon->foundationPile[i] = NULL;
	}
	/*yukon->foundation_CLUBS = 0;
	yukon->foundation_DIAMONDS = 0;
	yukon->foundation_HEARTS = 0;
	yukon->foundation_SPADES = 0;*/
}

void ExposeYukonCards(YukonStructure *yukon, const int amt_to_expose, const int *columnHeightArray) {
	for (int i = 0; i < COLUMN_SIZE; i++) {
		ll_node_card *card = yukon->columnFront[i];
		for (int a = 0; a < columnHeightArray[i]; a++) {
			card->card.hidden = (columnHeightArray[i] - a > amt_to_expose);
			card = card->next;
		}
	}
}

ll_node_card *DuplicateCardNode(ll_node_card *card, bool hidden) {
	ll_node_card *newcard = (ll_node_card *) malloc(sizeof(ll_node_card));
	newcard->card.card_value = card->card.card_value;
	newcard->card.suit = card->card.suit;
	newcard->card.hidden = hidden;
	newcard->next = NULL;
	return newcard;
}

void ClearGame(YukonStructure *yukon) {
	for (int i = 0; i < COLUMN_SIZE; i++) { yukon->columnFront[i] = NULL; } // init columns to null
	for (int i = 0; i < FOUNDATION_SIZE; i++) { yukon->foundationPile[i] = NULL; } // init foundations to null
}
