#ifndef yukon_model_h
#define yukon_model_h

#include "linkedlist.h"

typedef struct yukonStruct { // linked list node
    ll_node_card *Column_1_FRONT;
    ll_node_card *Column_2_FRONT;
    ll_node_card *Column_3_FRONT;
    ll_node_card *Column_4_FRONT;
    ll_node_card *Column_5_FRONT;
    ll_node_card *Column_6_FRONT;
    ll_node_card *Column_7_FRONT;

    int foundation_CLUBS;
    int foundation_DIAMONDS;
    int foundation_HEARTS;
    int foundation_SPADES;
} YukonStructure;

void DeckToYukon(ll_node_card *deck, YukonStructure *yukon);

#endif

