#include "linkedlist.h"

void appendToEnd(ll_node_int **list, int number) {
    if (!*list) { // list is null
        ll_node_int elem;
        elem.val = number;
        elem.next = NULL;
        *list = &elem;
        return;
    } else {
        ll_node_int *elem = list;
        while (elem->next != NULL) {
            elem = elem->next;
        }
        appendToElement(elem, number);
    }

}

void appendToElement(ll_node_int *elem, int number) {
    ll_node_int newelem;
    newelem.val = number;
    newelem.next = NULL;
    elem->next = &newelem;
}