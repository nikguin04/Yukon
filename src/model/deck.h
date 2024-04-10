#ifndef deck_h
#define deck_h
#include "card.h"
#define DECK_LENGTH 52

Card defaultDeck[DECK_LENGTH];

ll_node_card* LoadDeck(char* path, char** msg);
void PrintDeck(ll_node_card *carddeck);
ll_node_card* OpenDefaultDeck();

#endif