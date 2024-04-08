#ifndef linkedlist_h
#define linkedlist_h
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
ll_node_int* appendElement(int number);

#endif