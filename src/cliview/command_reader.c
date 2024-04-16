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
		} else {
			Move move = MatchMove(string);
			if (move.from != 0) {
				if (writer->ctrl->model->yukon->play_phase)
					writer->last_command_result = PerformMove(writer->ctrl, move);
				else
					writer->last_command_result = "Can't make moves when not playing";
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
		if (input[2] != ':') return move;
		Card card = MatchCard(input + 3);
		if (card.suit == 0) return move;
		move.card = card;
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

Card MatchCard(const char *input) {
	Card card = {};
	CardSuit suit = (CardSuit) input[1];
	// Not the prettiest to list them out, but it works...
	if (suit != CLUBS &&
	    suit != DIAMONDS &&
	    suit != HEARTS &&
	    suit != SPADES)
		return card;
	char value = input[0];
	switch (value) {
		case 'A': value = 1; break;
		case 'T': value = 10; break;
		case 'J': value = 11; break;
		case 'Q': value = 12; break;
		case 'K': value = 13; break;
		default: value = (char) (value - '0');
			if (value < 2 || value > 9) return card;
	}
	card.value = value;
	card.suit = suit;
	return card;
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
