#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdlib.h>

#define MIN_CARD 1
#define MAX_CARD 13

typedef enum : char {
	CLUBS = 'C',
	DIAMONDS = 'D',
	HEARTS = 'H',
	SPADES = 'S'
} CardSuit;

typedef struct cardStruct {
	char card_value;
	CardSuit suit;
	bool hidden;
} Card;

#include "linkedlist.h"

#endif

#ifdef LINKEDLIST_H_FINALIZED
#ifndef CARD_LL_H
#define CARD_LL_H

Card *CreateCard(int card_value, CardSuit suit);
ll_node_card *ParseCharCard(const char *card, const char **msg);
ll_node_card *NewCardAllocate(int value, CardSuit suit);
ll_node_card *CardToLinkedCard(Card *c);

char *cardToString(Card *card, char *out);
int getCardAbsoluteIndex(Card *card); // Index in a unshuffled deck

//#include "deck.h"

#endif
#endif
