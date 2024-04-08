#ifndef yukon_model_h
#define yukon_model_h

#include "linkedlist.h"

#define COLUMN_SIZE 7
static const int COLUMN_STARTSIZE[7] = {1, 6, 7, 8, 9, 10, 11};


typedef struct yukonStruct { // linked list node
    ll_node_card *Column_FRONT[COLUMN_SIZE];

    int foundation_CLUBS;
    int foundation_DIAMONDS;
    int foundation_HEARTS;
    int foundation_SPADES;
} YukonStructure;

void DeckToYukon(ll_node_card *deck, YukonStructure *yukon);

#endif

