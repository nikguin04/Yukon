#ifndef CARDSHUFFLER_H
#define CARDSHUFFLER_H

#include "linkedlist.h"

ll_node_card *shuffleInterleaving(ll_node_card *deckPointer, int split);
ll_node_card *shuffleRandom(ll_node_card *deckPointer);

#endif
