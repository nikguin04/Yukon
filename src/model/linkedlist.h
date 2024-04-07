#ifndef linkedlist_h
#define linkedlist_h
#include <stdio.h>

typedef struct ll_node { // linked list node
    int val;
    struct ll_node * next;
} ll_node_int;

void appendToEnd(ll_node_int **list, int number);
void appendToElement(ll_node_int *elem, int number);

#endif