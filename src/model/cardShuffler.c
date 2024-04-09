//
// Created by AGS17 on 4/8/2024.
//

#include "cardShuffler.h"
#include "card.h"
#include "linkedlist.h"
#include <stdbool.h>



ll_node_card *shuffleInterleaving(ll_node_card** deckptr, int split) {
    ll_node_card *deckPointer = *deckptr;

    ll_node_card* topSplitCardsFromDeck[split];
    ll_node_card* current_card = deckPointer;
    for(int i = 0; i<split; i++) {
        topSplitCardsFromDeck[i] = current_card;
        current_card = current_card -> next;
        ll_node_card* tmp = deckPointer;
        deckPointer = deckPointer -> next;
    }

    ll_node_card* shuffledDeck = NULL;
    int counter = 0;
    while (deckPointer != NULL && counter < split) {
            appendCardToStartOfList(&shuffledDeck, deckPointer->card);
            deckPointer = deckPointer -> next;
        if (counter < split) {
            appendCardToStartOfList(&shuffledDeck, topSplitCardsFromDeck[counter]->card);

        }
        counter++;
    }
    if(counter >= split) {
        while(deckPointer != NULL) {
            appendCardToEndOfList(&shuffledDeck, deckPointer->card);
            deckPointer = deckPointer->next;
        }
    }

    else if(deckPointer == NULL) {
        while(counter < split) {
            appendCardToEndOfList(&shuffledDeck, topSplitCardsFromDeck[counter]->card);
            counter++;
        }
    }
    return shuffledDeck;
}

ll_node_card *shuffleRandom(ll_node_card** deckptr) {

    ll_node_card *shuffledDeck = NULL;


}