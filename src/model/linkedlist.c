#include "linkedlist.h"

void appendToEnd(ll_node_int **list, int number) {
    if (!*list) { // list is null
        /*ll_node_int elem;
        elem.val = number;
        elem.next = NULL;
        *list = &elem;*/
        *list = appendElement(number);
        return;
    } else {
        //ll_node_int *first = *list;
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

    /*ll_node_int newelem;
    newelem.val = number;
    newelem.next = NULL;
    elem->next = &newelem;*/
}