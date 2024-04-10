#ifndef card_h
#define card_h
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MIN_CARD 1
#define MAX_CARD 13


typedef enum {
    CLUBS = 'C',
    DIAMONDS = 'D',
    HEARTS = 'H',
    SPADES = 'S'
} CardSuit;

typedef struct cardStruct { // linked list node
    int card_value;
    CardSuit suit;
    bool hidden;
} Card;

#include "linkedlist.h"
#endif

#ifdef linkelist_h_finalized
    #ifndef card_ll_h
    #define card_ll_h
    
	bool SaveDeck(ll_node_card *deck, const char *path);
	Card *createCard(int card_value, CardSuit suit);
    ll_node_card* ParseCharCard(char* card, char** msg);
    ll_node_card* NewCardAllocate(int value, CardSuit suit);
    ll_node_card* CardToLinkedCard(Card *c);

    char* cardToString(Card *card, char* out);

    #include "deck.h"
    void test();
    #endif

#endif