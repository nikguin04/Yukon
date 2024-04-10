#include "yukon_model.h"

void YukonToDeck(ll_node_card *deck, YukonStructure *yukon) { // Puts columns into a deck again // DO NOT USE, NOT IN GAME RULES!
	deck = yukon->Column_FRONT[0];
	ll_node_card *movingdeck = deck;
	yukon->Column_FRONT[0] = NULL;
	for (int i = 1; i < COLUMN_SIZE; i++) {
		movingdeck->next = yukon->Column_FRONT[i];
		yukon->Column_FRONT[i] = NULL;
		while (movingdeck->next != NULL) { movingdeck = movingdeck->next; };
	}
}

void DeckToYukon(ll_node_card *deck, YukonStructure *yukon, const int *Column_Height_Array) { // Puts the deck into column structure according to yukon rules

	ll_node_card *Column_TAIL[COLUMN_SIZE];
	ll_node_card *deckindex = deck;
	if (!deckindex) {
		printf("Exiting due to nulled deck passed to DeckToYukon()\n");
		exit(0);
	};
	for (int i = 0; i < COLUMN_SIZE; i++) {
		yukon->Column_FRONT[i] = DuplicateCardNode(deckindex, true);
		Column_TAIL[i] = yukon->Column_FRONT[i];
		deckindex = deckindex->next;
	} // Height = 1

	int height = 0;
	bool atend = false;
	while (!atend) {
		height++;
		atend = true;
		for (int i = 0; i < COLUMN_SIZE; i++) {
			if (Column_Height_Array[i] > height) {
				atend = false;
				Column_TAIL[i]->next = DuplicateCardNode(deckindex, true);
				Column_TAIL[i] = Column_TAIL[i]->next;
				deckindex = deckindex->next;
			}
		}
	}

	yukon->foundation_CLUBS = 0;
	yukon->foundation_DIAMONDS = 0;
	yukon->foundation_HEARTS = 0;
	yukon->foundation_SPADES = 0;
}

ll_node_card *DuplicateCardNode(ll_node_card *card, bool hidden) {
	ll_node_card *newcard = (ll_node_card *) malloc(sizeof(ll_node_card));
	newcard->card.card_value = card->card.card_value;
	newcard->card.suit = card->card.suit;
	newcard->card.hidden = hidden;
	newcard->next = NULL;
	return newcard;
}
