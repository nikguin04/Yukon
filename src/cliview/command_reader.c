#include "command_reader.h"

Command commands[] = {
	{"LD", "Load", LoadDeckFromFile},
	{"SD", "Save", SaveDeckToFile},
	{"SW", "Show", ShowDeck},
	{"SI", "Interleaving Shuffle", ShuffleInterleaving},
    {"SR", "Random Shuffle", ShuffleRandom},
    {}
};

void StartReadingLoop(CliWriter *writer) {
	while (true) { // Continues until user quits
		char *string = NULL;
		size_t size = 0;
		size_t len = 0;
		GetInput(&string, &size, &len);
		// Free last commands from writer
		free(writer->last_command);
		//free(writer->last_command_result); // Maybe this is not needed! check this if writing result messages fails
		writer->last_command = string;

		Command *cmd = MatchCommand(string);

		char *parsed_arg;
		if (cmd != NULL) {
			parsed_arg = CmdArgParse(string + strlen(cmd->input));
			writer->last_command_result = cmd->function(writer->ctrl, parsed_arg);
		} else { // else if: check that it could be a move
            int ismove = MatchMove(string);
            if (ismove) {
                writer->last_command_result = "Game move detected, but function is not implemented yet";
            } else {
                writer->last_command_result = "No command found!";
            }

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

Command *MatchCommand(char *cmdinput) {
	if (strlen(cmdinput) == 0) {
		printf("Command input is empty!\n"); // handle this properly
		return NULL;
	}

    for (int i = 0; i < 3; i++) { // TODO: HARDCODED, spørg worsøe
        bool test = (cmdinput == strstr(cmdinput, commands[i].input));// Check if input starts with command
        if (!test) { continue;}
        char *nextptr = cmdinput + strlen(commands[i].input);
        if (nextptr[0] == 0 || nextptr[0] == ' ') {
            return &commands[i];
        }
    }
    return 0;
}

int MatchMove(char *mvinput) {
    char from[6];
    char to[3];
    int initret = sscanf(mvinput, "%5[^-]\x2D>%s", from, to);
    // DO ALL GAME MOVE VALIDATION HERE!
    return initret==2; // no move found?
}

void GetInput(char **string, size_t *size, size_t *len) {
	getline(string, size, stdin);
	if (size < 0) {
		puts("couldn't read the input");
		free(*string);
		return;
	}
	*len = strlen(*string);


	// print the string
	//printf("<%s> is length %ld\n", *string, *len);

	// free the memory used by string when returned!
}

size_t getline(char **lineptr, size_t *n, FILE *stream) {
	char *bufptr = NULL;
	char *p = bufptr;
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
		*p++ = c; // put this behind the \n check is we want to include \n

		c = fgetc(stream);
	}

	*p++ = '\0';
	*lineptr = bufptr;
	*n = size;

	return p - bufptr - 1;
}
