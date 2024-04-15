#ifndef COMMAND_READER_H
#define COMMAND_READER_H

#include <string.h>
#include "writer.h"
#include "screen.h"
#include "../controller/command_controller.h"
#include "../model/move.h"

typedef const char *(*CommandFunction)(Controller *, char *);
typedef struct commandStruct {
	const char *input;
	const char *friendly_name;
	const CommandFunction function;
} Command;

extern const Command commands[];
#define COMMAND_COUNT sizeof(commands) / sizeof(commands[0])

[[noreturn]] void StartReadingLoop(CliWriter *writer);
const Command *MatchCommand(const char *cmdinput);
Move MatchMove(const char *input);
char MatchPile(const char *input);
Card MatchCard(const char *input);
void GetInput(char **string, size_t *size, size_t *len);
size_t getline(char **lineptr, size_t *n, FILE *stream);
char *CmdArgParse(char *input);

#endif
