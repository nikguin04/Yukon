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
        printf("value: %d, suit: %c", current_card->card.card_value, current_card->card.suit);
        topSplitCardsFromDeck[i] = current_card;
        current_card = current_card -> next;

        ll_node_card* tmp = deckPointer;
        deckPointer = deckPointer -> next;
        free(tmp);
    }

    ll_node_card* shuffledDeck = NULL;
    int counter = 0;
    while (deckPointer != NULL || counter < split) {

        if(deckPointer != NULL) {
            appendCardToEnd(&shuffledDeck, deckPointer->card);
            deckPointer = deckPointer -> next;
        }
        if (counter < split) {
            printf("value: %d, suit: %c", topSplitCardsFromDeck[counter]->card.card_value, topSplitCardsFromDeck[counter]->card.suit);
            appendCardToEnd(&shuffledDeck, topSplitCardsFromDeck[counter]->card);

        }
        counter++;
    }
    return shuffledDeck;
}