#include "deck.h"

void PrintDeck(ll_node_card *deck) {
	ll_node_card *current = deck;
	int progress = 0;
	while (current != NULL) {
		printf("card number %d = val: %d, suit: %d\n", progress++, current->card.card_value, current->card.suit);
		current = current->next;
	}
}

ll_node_card *LoadDeck(const char *path, char **msg) {
	FILE *ptr;
	char readbuffer[4];
	char *ch = readbuffer;

	// Open the file in read mode
	if (path == NULL) {
		*msg = "No path given to LoadDeck";
		return OpenDefaultDeck();
	}
	ptr = fopen(path, "r");

	if (NULL == ptr) {
		*msg = "File can't be opened";
		return OpenDefaultDeck();
	}

	ll_node_card *first_card = NULL;
	ll_node_card *current_card = NULL;
	int depth_counter = 0;
	do {
		*ch = fgetc(ptr);
		if (*ch == '\n' || *ch == EOF) {
			depth_counter++;
			//*ch == NULL;
			ll_node_card *card = ParseCharCard(readbuffer, msg);
			if (card == NULL) {
				return OpenDefaultDeck();
			};
			if (first_card == NULL) {
				first_card = card;
				current_card = card;
			} else {
				current_card->next = card;
				current_card = current_card->next;
				current_card->next = NULL;
			}

			ch = readbuffer;
		} else if (ch - readbuffer >= 2) {
			*msg = "Format is wrong, read 3 or more characters on one line";
			return OpenDefaultDeck();
		} else {
			ch++;
		}
		// If character is EOF, stop reading
	} while (readbuffer[2] != EOF); // WARNING: This will fail if format is incorrect, but we catch that in an if statement

	// Close the file again
	fclose(ptr);
	if (depth_counter != DECK_LENGTH) {
		*msg = "Wrong size of deck loaded. Expected 52"; // hardcoded to 52
		return OpenDefaultDeck();
	}
	*msg = "OK";
	return first_card;
}

bool SaveDeck(ll_node_card *deck, const char *path, char **msg) {
	if (path == NULL) {
		*msg = "No filename given";
		return false;
	}

	FILE *file;

	// Open the file in write mode
	file = fopen(path, "w");

	if (file == NULL) {
		*msg = "Couldn't open file to save deck";
		return false;
	}

	ll_node_card *card = deck;
	while (true) {
		char value;
		switch (card->card.card_value) {
			case 1: value = 'A'; break;
			case 10: value = 'T'; break;
			case 11: value = 'J'; break;
			case 12: value = 'Q'; break;
			case 13: value = 'K'; break;
			default: value = '0' + card->card.card_value;
		}
		fputc(value, file);
		fputc(card->card.suit, file);
		card = card->next;
		if (ferror(file)) {
			fclose(file);
			*msg = "Error writing to file";
			return false;
		}
		if (card == NULL) break;
		// If there's a next card, put a newline, otherwise don't
		// Because apparently final newlines aren't allowed for some reason?
		fputc('\n', file);
	}

	// Close the file again
	fclose(file);
	*msg = "OK";
	return true;
}

ll_node_card *OpenDefaultDeck() {
	ll_node_card *first = CardToLinkedCard(&defaultDeck[0]);
	ll_node_card *ptr = first;
	for (int i = 1; i < DECK_LENGTH; i++) {
		ptr->next = CardToLinkedCard(&defaultDeck[i]);
		ptr = ptr->next;
	}
	return first;
}

Card defaultDeck[DECK_LENGTH] = {
	{1,  CLUBS,    false},
	{2,  CLUBS,    false},
	{3,  CLUBS,    false},
	{4,  CLUBS,    false},
	{5,  CLUBS,    false},
	{6,  CLUBS,    false},
	{7,  CLUBS,    false},
	{8,  CLUBS,    false},
	{9,  CLUBS,    false},
	{10, CLUBS,    false},
	{11, CLUBS,    false},
	{12, CLUBS,    false},
	{13, CLUBS,    false},
	{1,  DIAMONDS, false},
	{2,  DIAMONDS, false},
	{3,  DIAMONDS, false},
	{4,  DIAMONDS, false},
	{5,  DIAMONDS, false},
	{6,  DIAMONDS, false},
	{7,  DIAMONDS, false},
	{8,  DIAMONDS, false},
	{9,  DIAMONDS, false},
	{10, DIAMONDS, false},
	{11, DIAMONDS, false},
	{12, DIAMONDS, false},
	{13, DIAMONDS, false},
	{1,  HEARTS,   false},
	{2,  HEARTS,   false},
	{3,  HEARTS,   false},
	{4,  HEARTS,   false},
	{5,  HEARTS,   false},
	{6,  HEARTS,   false},
	{7,  HEARTS,   false},
	{8,  HEARTS,   false},
	{9,  HEARTS,   false},
	{10, HEARTS,   false},
	{11, HEARTS,   false},
	{12, HEARTS,   false},
	{13, HEARTS,   false},
	{1,  SPADES,   false},
	{2,  SPADES,   false},
	{3,  SPADES,   false},
	{4,  SPADES,   false},
	{5,  SPADES,   false},
	{6,  SPADES,   false},
	{7,  SPADES,   false},
	{8,  SPADES,   false},
	{9,  SPADES,   false},
	{10, SPADES,   false},
	{11, SPADES,   false},
	{12, SPADES,   false},
	{13, SPADES,   false}
};
