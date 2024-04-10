#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include "card.h"

typedef struct ll_node_c { // linked list node
	Card card;
	struct ll_node_c *next;
} ll_node_card;

typedef struct ll_node_i { // linked list node
	int val;
	struct ll_node_i *next;
} ll_node_int;

void appendToEnd(ll_node_int **list, int number);
ll_node_int *appendElement(int number);
void appendCardToEndOfList(ll_node_card **list, Card card);
void appendCardToStartOfList(ll_node_card **list, Card card);
ll_node_card *appendCardElement(Card card);
void insertCardAtIndex(ll_node_card **list, Card card, int index);

// Reload card.h for load function
#define LINKEDLIST_H_FINALIZED
#include "card.h"

#endif
