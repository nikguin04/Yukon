#include "deck.h"

void PrintDeck(ll_node_card *deck) {
	ll_node_card *current = deck;
	int progress = 0;
	while (current != NULL) {
		printf("card number %d = val: %d, suit: %d\n", progress++, current->card.value, current->card.suit);
		current = current->next;
	}
}

ll_node_card *LoadDeck(const char *path, const char **msg) {
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
		*ch = (char) fgetc(ptr);
		if (*ch == '\n' || *ch == EOF) {
			depth_counter++;
			//*ch == NULL;
			ll_node_card *card = ParseCharCard(readbuffer, msg);
			if (card == NULL) {
				return OpenDefaultDeck();
			}
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

bool SaveDeck(ll_node_card *deck, const char *path, const char **msg) {
	if (path == NULL) {
		path = "cards.txt";
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
		switch (card->card.value) {
			case 1: value = 'A'; break;
			case 10: value = 'T'; break;
			case 11: value = 'J'; break;
			case 12: value = 'Q'; break;
			case 13: value = 'K'; break;
			default: value = (char) ('0' + card->card.value);
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
	ptr->next = NULL;
	return first;
}

Card defaultDeck[DECK_LENGTH] = {
	{1,  CLUBS},
	{2,  CLUBS},
	{3,  CLUBS},
	{4,  CLUBS},
	{5,  CLUBS},
	{6,  CLUBS},
	{7,  CLUBS},
	{8,  CLUBS},
	{9,  CLUBS},
	{10, CLUBS},
	{11, CLUBS},
	{12, CLUBS},
	{13, CLUBS},
	{1,  DIAMONDS},
	{2,  DIAMONDS},
	{3,  DIAMONDS},
	{4,  DIAMONDS},
	{5,  DIAMONDS},
	{6,  DIAMONDS},
	{7,  DIAMONDS},
	{8,  DIAMONDS},
	{9,  DIAMONDS},
	{10, DIAMONDS},
	{11, DIAMONDS},
	{12, DIAMONDS},
	{13, DIAMONDS},
	{1,  HEARTS},
	{2,  HEARTS},
	{3,  HEARTS},
	{4,  HEARTS},
	{5,  HEARTS},
	{6,  HEARTS},
	{7,  HEARTS},
	{8,  HEARTS},
	{9,  HEARTS},
	{10, HEARTS},
	{11, HEARTS},
	{12, HEARTS},
	{13, HEARTS},
	{1,  SPADES},
	{2,  SPADES},
	{3,  SPADES},
	{4,  SPADES},
	{5,  SPADES},
	{6,  SPADES},
	{7,  SPADES},
	{8,  SPADES},
	{9,  SPADES},
	{10, SPADES},
	{11, SPADES},
	{12, SPADES},
	{13, SPADES},
};
