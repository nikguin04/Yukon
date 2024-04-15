#ifndef COMMAND_READER_H
#define COMMAND_READER_H

#include <string.h>
#include "writer.h"
#include "../controller/command_controller.h"
#include "screen.h"

typedef const char *(*CommandFunction)(Controller *, char *);
typedef struct commandStruct {
	const char *input;
	const char *friendly_name;
	const CommandFunction function;
} Command;

extern const Command commands[];
#define COMMAND_COUNT sizeof(commands) / sizeof(commands[0])

// WORSØE PLEASE FIX WITH BEAUTIFUL MACRO!
typedef struct ll_node_cmd { // linked list node
	Command *command;
	struct ll_node_cmd *next;
	bool skip;
} ll_node_command;

void StartReadingLoop(CliWriter *writer);
const Command *MatchCommand(const char *cmdinput);
void GetInput(char **string, size_t *size, size_t *len);
size_t getline(char **lineptr, size_t *n, FILE *stream);
char *CmdArgParse(char *input);

#endif
