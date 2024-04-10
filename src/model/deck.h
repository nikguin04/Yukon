#ifndef deck_h
#define deck_h
#include "card.h"
#define DECK_LENGTH 52

ll_node_card* LoadDeck(char* path);
void PrintDeck(ll_node_card *carddeck);

#endif