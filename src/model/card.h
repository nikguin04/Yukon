#ifndef card_h
#define card_h
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MIN_CARD 1
#define MAX_CARD 13


/*typedef enum {
    A = 'A',
    TWO = '2',
    THREE = '3',
    FOUR = '4',
    FIVE = '5',
    SIX = '6',
    SEVEN = '7',
    EIGHT = '8',
    NINE = '9',
    TEN = '10',
    JACK = 'J',
    QUEEN = 'Q',
    KING = 'K'
} CardValue;*/

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
    

    ll_node_card* ParseCharCard(char* card, char** msg);
    ll_node_card* NewCardAllocate(int value, CardSuit suit);
    ll_node_card* CardToLinkedCard(Card *c);

    char* cardToString(Card *card, char* out);

    #include "deck.h"
    void test();
    #endif

#endif