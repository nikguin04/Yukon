#ifndef WRITER_H
#define WRITER_H

#include <stdio.h>
#include "../controller/controller.h"
#include "../model/linkedlist.h"
#include "printer.h"

typedef struct CliWriterStructure {
	Controller *ctrl;
	char *last_command;
	char *last_command_result;
} CliWriter;

void initWriter(CliWriter *writer, Controller *ctrl);

#endif
