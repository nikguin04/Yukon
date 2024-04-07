#ifndef linkedlist_h
#define linkedlist_h
#include <stdio.h>
#include <stdlib.h>

typedef struct ll_node { // linked list node
    int val;
    struct ll_node * next;
} ll_node_int;

void appendToEnd(ll_node_int **list, int number);
ll_node_int* appendElement(int number);

#endif