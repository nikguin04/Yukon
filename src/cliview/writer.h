#ifndef writer_h
#define writer_h
#include <stdio.h>
#include "../controller/controller.h"
#include "../model/linkedlist.h"

//extern struct ControlStucture;
//typedef struct ControlStucture Controller;



struct CliWriterStucture { // linked list node
    Controller *ctrl;
};
typedef struct CliWriterStucture CliWriter;

int readToArray(CliWriter *writer);
void printList(ll_node_int *list);

CliWriter initWriter(Controller *ctrl);
#endif

