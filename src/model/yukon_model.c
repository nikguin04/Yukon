#include "yukon_model.h"

void DeckToYukon(ll_node_card *deck, YukonStructure *yukon) {
    // This code is a little spaghetti, but i am lazy and it works right now
    ll_node_card *setnull;

    yukon->Column_1_FRONT = deck;
    setnull = deck; deck = deck->next; setnull->next = NULL;

    yukon->Column_2_FRONT = deck;
    for (int i = 0; i < 5; i++) { deck = deck->next; }
    setnull = deck; deck = deck->next; setnull->next = NULL;

    yukon->Column_3_FRONT = deck;
    for (int i = 0; i < 6; i++) { deck = deck->next; }
    setnull = deck; deck = deck->next; setnull->next = NULL;

    yukon->Column_4_FRONT = deck;
    for (int i = 0; i < 7; i++) { deck = deck->next; }
    setnull = deck; deck = deck->next; setnull->next = NULL;
    
    yukon->Column_5_FRONT = deck;
    for (int i = 0; i < 8; i++) { deck = deck->next; }
    setnull = deck; deck = deck->next; setnull->next = NULL;

    yukon->Column_6_FRONT = deck;
    for (int i = 0; i < 9; i++) { deck = deck->next; }
    setnull = deck; deck = deck->next; setnull->next = NULL;

    yukon->Column_7_FRONT = deck;
    for (int i = 0; i < 10; i++) { deck = deck->next; }
    setnull = deck; deck = deck->next; setnull->next = NULL;


    yukon->foundation_CLUBS = 0;
    yukon->foundation_DIAMONDS = 0;
    yukon->foundation_HEARTS = 0;
    yukon->foundation_SPADES = 0;
}