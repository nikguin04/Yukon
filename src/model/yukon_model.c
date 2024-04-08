#include "yukon_model.h"

void DeckToYukon(ll_node_card *deck, YukonStructure *yukon) {
    // This code is a little spaghetti, but i am lazy and it works right now
    ll_node_card *setnull;
    
    for (int i = 0; i < COLUMN_SIZE; i++) {
        yukon->Column_FRONT[i] = deck;
        for (int a = 0; a < COLUMN_STARTSIZE[i]-1; a++) {
            deck = deck->next;
        }
        setnull = deck; deck = deck->next; setnull->next = NULL;
    }


    yukon->foundation_CLUBS = 0;
    yukon->foundation_DIAMONDS = 0;
    yukon->foundation_HEARTS = 0;
    yukon->foundation_SPADES = 0;
}