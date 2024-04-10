#include "card.h"

void test() {
    Card somecard;
    somecard.card_value = 8;
    somecard.suit = SPADES;
    return;
}



ll_node_card* ParseCharCard(char* card, char** msg) {
    int val = card[0];
    int isuit = card[1];
    CardSuit suit;
    int cardint;
    switch (isuit)
    {
        case 'C': suit = CLUBS; break;
        case 'D': suit = DIAMONDS; break;
        case 'H': suit = HEARTS; break;
        case 'S': suit = SPADES; break;
    
        default:
            *msg = "Format of file is wrong, did not read suit correctly";
            return NULL;
    }

    switch (val)
    {
        case 'A': cardint = 1; break;
        case '2': cardint = 2; break;
        case '3': cardint = 3; break;
        case '4': cardint = 4; break;
        case '5': cardint = 5; break;
        case '6': cardint = 6; break;
        case '7': cardint = 7; break;
        case '8': cardint = 8; break;
        case '9': cardint = 9; break;
        case 'T': cardint = 10; break;
        case 'J': cardint = 11; break;
        case 'Q': cardint = 12; break;
        case 'K': cardint = 13; break;
    
        default:
            *msg = "Format of file is wrong, did not read card number correctly";
            return NULL;
    }

    return NewCardAllocate(cardint, suit);
}

ll_node_card* NewCardAllocate(int value, CardSuit suit) {
    ll_node_card *card = (ll_node_card*) malloc(sizeof(ll_node_card));
    card->card.card_value = value;
    card->card.suit = suit;
    return card;
}

ll_node_card* CardToLinkedCard(Card *c) {
    ll_node_card *card = (ll_node_card*) malloc(sizeof(ll_node_card));
    card->card.card_value = c->card_value;
    card->card.hidden = c->hidden;
    card->card.suit = c->suit;
    return card;
}


char* cardToString(Card *card, char* cardStr) {
    cardStr[2] = NULL;

    switch (card->card_value)
    {
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
            return;
    }

    cardStr[1] = card->suit;
    return cardStr;
}

