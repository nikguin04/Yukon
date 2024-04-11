#ifndef COMMAND_READER_H
#define COMMAND_READER_H

#include <string.h>
#include "writer.h"
#include "../controller/command_controller.h"
#include "screen.h"

typedef char *(*CommandFunction)(Controller *, char *);
typedef struct commandStruct {
	char *input;
	char *friendly_name;
	CommandFunction function;
} Command;

extern Command commands[];

// WORSØE PLEASE FIX WITH BEAUTIFUL MACRO!
typedef struct ll_node_cmd { // linked list node
	Command *command;
	struct ll_node_cmd *next;
	bool skip;
} ll_node_command;

void StartReadingLoop(CliWriter *writer);
Command *MatchCommand(char *cmdinput, size_t *len);
void GetInput(char **string, size_t *size, size_t *len);
size_t getline(char **lineptr, size_t *n, FILE *stream);
char *CmdArgParse(char *input);

#endif
