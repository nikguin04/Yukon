#include "card.h"

Card *CreateCard(int value, CardSuit suit) {
	Card *card = malloc(sizeof(Card));
	card->value = value;
	card->suit = suit;
	return card;
}

ll_node_card *ParseCharCard(const char *card, const char **msg) {
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
	card->card.value = value;
	card->card.suit = suit;
	card->hidden = false;
	return card;
}

ll_node_card *CardToLinkedCard(Card *c) {
	ll_node_card *card = (ll_node_card *) malloc(sizeof(ll_node_card));
	card->card.value = c->value;
	card->card.suit = c->suit;
	card->hidden = false;
	return card;
}

char *cardToString(Card *card, char *cardStr) { // memory leak, not freed?
	cardStr[2] = 0;

	switch (card->value) {
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
