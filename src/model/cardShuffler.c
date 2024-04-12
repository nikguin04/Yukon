#include "cardShuffler.h"
#include "card.h"
#include "linkedlist.h"
#include <stdlib.h>
#include <stdbool.h>

ll_node_card *shuffleInterleaving(ll_node_card *deckPointer, int split, char** msg, bool randSplit) {
    ll_node_card *originalDeckPointer = deckPointer;
    if (randSplit) {
        split = (rand() % 52) + 1;
        *msg = "Deck shuffled with random split";
    }
    else if (split <= 0 || split >= 52) {
        *msg = "Incorrect input";
        return deckPointer;
    }
    else {
        *msg = "Deck shuffled with interleaving shuffle";
    }


	ll_node_card **topSplitCardsFromDeck = (ll_node_card **) malloc(sizeof(ll_node_card *) * split);
//	ll_node_card *current_card = deckPointer;
	for (int i = 0; i < split; i++) {
        topSplitCardsFromDeck[i] = deckPointer;
		deckPointer = deckPointer->next;
	}

	ll_node_card *shuffledDeck = NULL;
	int counter = 0;
	while (deckPointer != NULL && counter < split) {
		appendCardToStartOfList(&shuffledDeck, deckPointer->card);
		deckPointer = deckPointer->next;
		if (counter < split) {
			appendCardToStartOfList(&shuffledDeck, topSplitCardsFromDeck[counter]->card);

		}
		counter++;
	}
	if (counter >= split) {
		while (deckPointer != NULL) {
			appendCardToEndOfList(&shuffledDeck, deckPointer->card);
			ll_node_card *tmp = deckPointer;
            deckPointer = deckPointer->next;
		}
	} else if (deckPointer == NULL) {
		while (counter < split) {
			appendCardToEndOfList(&shuffledDeck, topSplitCardsFromDeck[counter]->card);
			counter++;
            freeList(deckPointer);
		}
	}
	free(topSplitCardsFromDeck);
    return shuffledDeck;
}

ll_node_card *shuffleRandom(ll_node_card *deckPointer) {
	ll_node_card *shuffledDeck = NULL;
	int counter = 1;
	while (deckPointer != NULL) {
		// Generate random number in range [1, counter]
		ll_node_card *tmp = deckPointer;
		deckPointer = deckPointer->next;

		int indexToPlaceCardAt = ((rand() % counter) + 1);
		insertCardAtIndex(&shuffledDeck, tmp->card, indexToPlaceCardAt);
		counter++;
		free(tmp);
	}
	return shuffledDeck;
}