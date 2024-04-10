#ifndef WRITER_H
#define WRITER_H

#include <stdio.h>
#include "../controller/controller.h"
#include "../model/linkedlist.h"
#include "printer.h"

//extern struct ControlStucture;
//typedef struct ControlStucture Controller;

struct CliWriterStucture {
	Controller *ctrl;
	char *last_command;
	char *last_command_result;
};
typedef struct CliWriterStucture CliWriter;

int readToArray(CliWriter *writer);
void printList(ll_node_int *list);

void initWriter(CliWriter *writer, Controller *ctrl);
void PromptLoadDeck(Controller *ctrl);
#endif
