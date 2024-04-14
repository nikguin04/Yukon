#include "command_reader.h"

const Command commands[] = {
	{"LD", "Load",                 LoadDeckFromFile},
	{"SD", "Save",                 SaveDeckToFile},
	{"SW", "Show",                 ShowDeck},
	{"SI", "Interleaving Shuffle", ShuffleInterleaving},
	{"SR", "Random Shuffle",       ShuffleRandom},
	{"QQ", "Quit and exit game",   QuitAndExit},
};

void StartReadingLoop(CliWriter *writer) {
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
		} else {
			Move move = MatchMove(string);
			if (move.from != 0) {
				// TODO: Handle move
			} else {
				writer->last_command_result = "Invalid command or move!";
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

const Command *MatchCommand(const char *cmdinput) {
	if (strlen(cmdinput) == 0) {
		printf("Command input is empty!\n");
		return NULL;
	}

	for (int i = 0; i < COMMAND_COUNT; i++) {
		// Check if input starts with command
		bool test = (cmdinput == strstr(cmdinput, commands[i].input));
		if (!test) { continue; }
		const char *nextptr = cmdinput + strlen(commands[i].input);
		if (nextptr[0] == 0 || nextptr[0] == ' ') {
			return &commands[i];
		}
	}
	return 0;
}

Move MatchMove(const char *input) {
	// Returned as-is if input was invalid
	Move move = {};
	size_t len = strlen(input);
	if (len != 6 && len != 9) return move;

	// Make a pointer at where the arrow should start (fourth last character)
	// Then check for the arrow and leave p right after, where the dest should be
	const char *p = input + (len - 4);
	if (*(p++) != '-' || *(p++) != '>') return move;

	// Try to parse the source and destination, and check that they're valid
	char from = MatchPile(input);
	char to = MatchPile(p);
	if (from == 0 || to == 0) return move;

	// If length is 9, a specific card is specified
	if (len == 9) {
		// You can't select a specific card from a foundation pile
		if (from < 0) return move;
		char cardValue;
		CardSuit cardSuit;
		if (input[2] != ':') return move;
		cardSuit = (CardSuit) input[4];
		// Not the prettiest to list them out, but it works...
		if (cardSuit != CLUBS &&
		    cardSuit != DIAMONDS &&
		    cardSuit != HEARTS &&
		    cardSuit != SPADES)
			return move;
		switch (input[3]) {
			case 'A': cardValue = 1; break;
			case 'T': cardValue = 10; break;
			case 'J': cardValue = 11; break;
			case 'Q': cardValue = 12; break;
			case 'K': cardValue = 13; break;
			default: cardValue = (char) (input[3] - '0');
				if (cardValue < 2 || cardValue > 9) return move;
		}
		move.fromCardValue = cardValue;
		move.fromCardSuit = cardSuit;
	}
	move.from = from;
	move.to = to;
	return move;
}

char MatchPile(const char *input) {
	int num = input[1] - '0';
	if (num < 1) return 0;
	else if (input[0] == 'C' && num <= 7) return (char) num;
	else if (input[0] == 'F' && num <= 4) return (char) -num;
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
		*p++ = c; // put this behind the \n check is we want to include \n

		c = fgetc(stream);
	}

	*p++ = '\0';
	*lineptr = bufptr;
	*n = size;

	return p - bufptr - 1;
}
