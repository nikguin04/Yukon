#include "linkedlist.h"

void appendToEnd(ll_node_int **list, int number) {
    if (!*list) { // list is null
        *list = appendElement(number);
        return;
    } else {
        ll_node_int *elem = *list;
        while (elem->next != NULL) {
            elem = elem->next;
        }
        elem->next = appendElement(number);
    }
}

ll_node_int* appendElement(int number) {
    ll_node_int *elem = (ll_node_int*) malloc(sizeof(ll_node_int));
    elem->val = number;
    elem->next = NULL;
    return elem;
}

void insertCardAtIndex(ll_node_card **list, Card card, int index) {
    ll_node_card *nodeToInsert = appendCardElement(card);
    if(!*list ) {
        *list = nodeToInsert;
    } else {

        ll_node_card *currentNode = *list;
        for (int i = 1; i < index - 1; i++) {
            if (currentNode->next != NULL) {
                currentNode = currentNode->next;
            } else {
                break;
            }
        }
        nodeToInsert->next = currentNode->next;
        currentNode->next = nodeToInsert;
    }
}

void appendCardToStartOfList(ll_node_card **list, Card card) {
    ll_node_card *newNode = appendCardElement(card);
    if (!*list) {
        *list = newNode;
        return;
    } else {
        newNode -> next = *list;
        *list = newNode;
    }
}

void appendCardToEndOfList(ll_node_card **list, Card card) {
    if (!*list) { // list is null
        *list = appendCardElement(card);
        return;
    } else {
        ll_node_card *elem = *list;
        while (elem->next != NULL) {
            elem = elem->next;
        }
        elem->next = appendCardElement(card);
    }
}

ll_node_card* appendCardElement(Card card) {
    ll_node_card *elem = (ll_node_card*) malloc(sizeof(ll_node_card));
    elem->card = card;
    elem->next = NULL;
    return elem;
}