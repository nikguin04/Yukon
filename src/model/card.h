#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_CARD 1
#define MAX_CARD 13

typedef enum : char {
	CLUBS = 'C',
	DIAMONDS = 'D',
	HEARTS = 'H',
	SPADES = 'S'
} CardSuit;

typedef struct cardStruct {
	char value;
	CardSuit suit;
} Card;

bool CardEquals(Card a, Card b);

#include "linkedlist.h"

#endif

#ifdef LINKEDLIST_H_FINALIZED
#ifndef CARD_LL_H
#define CARD_LL_H

Card *CreateCard(char value, CardSuit suit);
ll_node_card *ParseCharCard(const char *card, char *msg, int lineNumber);
ll_node_card *NewCardAllocate(char value, CardSuit suit);
ll_node_card *CardToLinkedCard(Card *card);

char *CardToString(Card card, char *cardStr);
int GetCardAbsoluteIndex(Card card); // Index in a unshuffled deck

//#include "deck.h"

#endif
#endif
