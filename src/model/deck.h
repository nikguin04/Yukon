#ifndef DECK_H
#define DECK_H

#include "card.h"

#define DECK_LENGTH 52

extern Card defaultDeck[DECK_LENGTH];

ll_node_card *LoadDeck(const char *path, char **msg);
bool SaveDeck(ll_node_card *deck, const char *path, char **msg);
void PrintDeck(ll_node_card *deck);
ll_node_card *OpenDefaultDeck();

#endif
