#include "command_reader.h"

const Command commands[] = {
	{"LD", "Load",                 LoadDeckFromFile},
	{"SD", "Save",                 SaveDeckToFile},
	{"SW", "Show",                 ShowDeck},
	{"SI", "Interleaving Shuffle", ShuffleInterleaving},
	{"SR", "Random Shuffle",       ShuffleRandom},
	{"QQ", "Quit and exit game",   QuitAndExit},
	{"Q",  "Quit game",            QuitGame},
	{"P",  "Play game",            PlayGame},
};

[[noreturn]] void StartReadingLoop(CliWriter *writer) {
	while (true) { // Continues until user quits
		char *string = NULL;
		size_t size = 0;
		size_t len = 0;
		GetInput(&string, &size, &len);
		// Free last commands from writer
		free(writer->last_command);
		writer->last_command = string;

		const Command *cmd = MatchCommand(string);

		char *parsed_arg;
		if (cmd != NULL) {
			parsed_arg = CmdArgParse(string + strlen(cmd->input));
			writer->last_command_result = cmd->function(writer->ctrl, parsed_arg);
		} else { // else if: check that it could be a move
			writer->last_command_result = "No command found!";
		}
		//free(string);
		UpdateScreen(writer);
	}
}

char *CmdArgParse(char *input) {
	if (input[0] == ' ') {
		return input + 1;
	} else {
		return NULL;
	}
}

const Command *MatchCommand(const char *input) {
	if (strlen(input) == 0) {
		printf("Command input is empty!\n");
		return NULL;
	}

	for (int i = 0; i < COMMAND_COUNT; i++) {
		// Check if input starts with command
		bool test = (input == strstr(input, commands[i].input));
		if (!test) { continue; }
		const char *nextptr = input + strlen(commands[i].input);
		if (nextptr[0] == 0 || nextptr[0] == ' ') {
			return &commands[i];
		}
	}
	return 0;
}

void GetInput(char **string, size_t *size, size_t *len) {
	getline(string, size, stdin);
	if (size < 0) {
		puts("couldn't read the input");
		free(*string);
		return;
	}
	*len = strlen(*string);

	// TODO: Free the memory used by string when returned?
}

size_t getline(char **lineptr, size_t *n, FILE *stream) {
	char *bufptr = NULL;
	char *p;
	size_t size;
	int c;

	if (lineptr == NULL || stream == NULL || n == NULL)
		return -1;
	bufptr = *lineptr;
	size = *n;

	c = fgetc(stream);
	if (c == EOF)
		return -1;
	if (bufptr == NULL) {
		bufptr = malloc(128);
		if (bufptr == NULL)
			return -1;
		size = 128;
	}
	p = bufptr;
	while (c != EOF) {
		if ((p - bufptr) > (size - 1)) {
			size = size + 128;
			bufptr = realloc(bufptr, size);
			if (bufptr == NULL)
				return -1;
		}
		if (c == '\n')
			break;
		*p++ = (char) c; // put this behind the \n check is we want to include \n

		c = fgetc(stream);
	}

	*p++ = '\0';
	*lineptr = bufptr;
	*n = size;

	return p - bufptr - 1;
}
