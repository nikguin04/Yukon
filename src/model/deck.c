#include "deck.h"

void PrintDeck(ll_node_card *carddeck) {
    ll_node_card *current = carddeck;
    int progress = 0;
    while (current != NULL) {
        printf("card number %d = val: %d, suit: %d\n", progress++, current->card.card_value, current->card.suit);
        current = current->next;
    }
}

ll_node_card* LoadDeck(char* path) {
    FILE* ptr;
    char readbuffer[4];
    char* ch = readbuffer;
 
    // Opening file in reading mode
    ptr = fopen(path, "r");
 
    if (NULL == ptr) {
        printf("file can't be opened \n");
        return NULL;
    }
    
    ll_node_card *first_card = NULL;
    ll_node_card *current_card = NULL;
    int depth_counter = 0;
    do {
        *ch = fgetc(ptr);
        if (*ch == '\n' || *ch == EOF) {
            depth_counter++;
            //*ch == NULL;
            ll_node_card *card = ParseCharCard(readbuffer);
            if (card == NULL) {return NULL;};
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
            printf("Format is wrong, read 3 or more characters on one line\n");
            return NULL;
        } else {
            ch++;
        }
        // Checking if character is not EOF.
        // If it is EOF stop reading.
    } while (readbuffer[2] != EOF); // warning: this will fail if format is incorrect. but we catch that in a if statement
 
    // Closing the file
    fclose(ptr);
    if (depth_counter != DECK_LENGTH) {
        printf("Wrong size of deck loaded, expected size (%d), got size (%d)\n", DECK_LENGTH, depth_counter);
        return NULL;
    }
    return first_card;
}