#include "card.h"

Card *CreateCard(int card_value, CardSuit suit) {
	Card *card = malloc(sizeof(Card));
	card->card_value = card_value;
	card->suit = suit;
	return card;
}

ll_node_card *ParseCharCard(const char *card, char **msg) {
	CardSuit suit = (CardSuit) card[1];
	int value;
	switch (suit) {
		case CLUBS:
		case DIAMONDS:
		case HEARTS:
		case SPADES:
			break;

		default:
			*msg = "Format of file is wrong, did not read suit correctly";
			return NULL;
	}

	switch (card[0]) {
		case 'A': value = 1; break;
		case '2': value = 2; break;
		case '3': value = 3; break;
		case '4': value = 4; break;
		case '5': value = 5; break;
		case '6': value = 6; break;
		case '7': value = 7; break;
		case '8': value = 8; break;
		case '9': value = 9; break;
		case 'T': value = 10; break;
		case 'J': value = 11; break;
		case 'Q': value = 12; break;
		case 'K': value = 13; break;

		default:
			*msg = "Format of file is wrong, did not read card number correctly";
			return NULL;
	}

	return NewCardAllocate(value, suit);
}

ll_node_card *NewCardAllocate(int value, CardSuit suit) {
	ll_node_card *card = (ll_node_card *) malloc(sizeof(ll_node_card));
	card->card.card_value = value;
	card->card.suit = suit;
	return card;
}

ll_node_card *CardToLinkedCard(Card *c) {
	ll_node_card *card = (ll_node_card *) malloc(sizeof(ll_node_card));
	card->card.card_value = c->card_value;
	card->card.hidden = c->hidden;
	card->card.suit = c->suit;
	return card;
}

char *cardToString(Card *card, char *cardStr) {
	cardStr[2] = 0;

	switch (card->card_value) {
		case 1: cardStr[0] = 'A'; break;
		case 2: cardStr[0] = '2'; break;
		case 3: cardStr[0] = '3'; break;
		case 4: cardStr[0] = '4'; break;
		case 5: cardStr[0] = '5'; break;
		case 6: cardStr[0] = '6'; break;
		case 7: cardStr[0] = '7'; break;
		case 8: cardStr[0] = '8'; break;
		case 9: cardStr[0] = '9'; break;
		case 10: cardStr[0] = 'T'; break;
		case 11: cardStr[0] = 'J'; break;
		case 12: cardStr[0] = 'Q'; break;
		case 13: cardStr[0] = 'K'; break;

		default:
			printf("Card number is out of bounds for parsing to string");
			return NULL;
	}

	cardStr[1] = card->suit;
	return cardStr;
}

bool SaveDeck(ll_node_card *deck, const char *path) {
	FILE *file;

	// Opening file in write mode
	file = fopen(path, "w");

	if (file == NULL) {
		printf("Couldn't open file to save deck\n");
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
			printf("Error writing to file\n");
			return false;
		}
		if (card == NULL) break;
		// If there's a next card, put a newline, otherwise don't
		// Because apparently final newlines aren't allowed for some reason?
		fputc('\n', file);
	}

	// Closing the file
	fclose(file);
	return true;
}
