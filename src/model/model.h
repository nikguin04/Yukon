#ifndef model_h
#define model_h
#include <stdio.h>
#include "../cliview/writer.h"
#include "linkedlist.h"


typedef struct ModelStucture Model;

int addToLinkedList(int *intptr);

Model initModel(CliWriter *writer);

#endif