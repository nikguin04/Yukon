#include "yukon_model.h"

void YukonToDeck(ll_node_card *deck, YukonStructure *yukon) { // Puts columns into a deck again

}

void DeckToYukon(ll_node_card *deck, YukonStructure *yukon) { // Puts the deck into column structure according to yukon rules
    // This code is a little spaghetti, but i am lazy and it works right now
    ll_node_card *setnull;
    if (!deck) {printf("Exiting due to nulled deck passed to DeckToYukon()\n"); exit(0);};
    
    for (int i = 0; i < COLUMN_SIZE; i++) {
        yukon->Column_FRONT[i] = deck;
        for (int a = 0; a < COLUMN_STARTSIZE[i]-1; a++) {
            // TODO: following line should probably only be visible when starting game (used for testing)
            deck->card.hidden = (COLUMN_STARTSIZE[i] - a > 5); // True when we are in the last 5 cards of a column (shown by default)
            deck = deck->next;
        }
        setnull = deck; deck = deck->next; setnull->next = NULL;
        setnull->card.hidden = false; // ALSO FOR TESTING HERE!, but this is how it should work in starting the game
    }


    yukon->foundation_CLUBS = 0;
    yukon->foundation_DIAMONDS = 0;
    yukon->foundation_HEARTS = 0;
    yukon->foundation_SPADES = 0;
}