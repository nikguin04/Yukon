//
// Created by AGS17 on 4/8/2024.
//

#include "cardShuffler.h"
#include "card.h"
#include "linkedlist.h"
#include <stdbool.h>



ll_node_card *shuffleInterleaving(ll_node_card** deckptr, int split) {
    ll_node_card *deckPointer = *deckptr;

// Testing stuff
//    ll_node_card *shuffledDeck = deckPointer;
//    Card *testCard = createCard(-1, 'C');
//    appendCardToStartOfList(&shuffledDeck, *testCard);
//    printf("val: %d, suit: %c\n", shuffledDeck -> card.card_value, shuffledDeck -> card.suit);

    ll_node_card* topSplitCardsFromDeck[split];
    ll_node_card* current_card = deckPointer;
    for(int i = 0; i<split; i++) {
//        printf("value: %d, suit: %c ", current_card->card.card_value, current_card->card.suit);
        topSplitCardsFromDeck[i] = current_card;
        current_card = current_card -> next;

//        printf("Value: %d, Suit: %c", topSplitCardsFromDeck[i]->card.card_value, topSplitCardsFromDeck[i]->card.suit);

        ll_node_card* tmp = deckPointer;
        deckPointer = deckPointer -> next;
//        free(tmp);
    }
        printf("\n");

    ll_node_card* shuffledDeck = NULL;
    int counter = 0;
    while (deckPointer != NULL || counter < split) {
        if(deckPointer != NULL) {
//            appendCardToEndOfList(&shuffledDeck, deckPointer->card);
            appendCardToStartOfList(&shuffledDeck, deckPointer->card);
            deckPointer = deckPointer -> next;

        }
        if (counter < split) {
//            printf("value: %d, suit: %c", topSplitCardsFromDeck[counter]->card.card_value, topSplitCardsFromDeck[counter]->card.suit);

//            appendCardToEndOfList(&shuffledDeck, topSplitCardsFromDeck[counter]->card);
            appendCardToStartOfList(&shuffledDeck, topSplitCardsFromDeck[counter]->card);

        }
        counter++;
    }
    return shuffledDeck;
}