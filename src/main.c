#include <stdio.h>
#include <model/model.h>
#include <controller/controller.h>
#include <cliview/writer.h>
#include <cardShuffler.h>
#include <time.h>


// THINGS TO FIX:


int main() {
	Model model;
	initModel(&model);
	Controller ctrl;
	initController(&ctrl, &model);
	CliWriter writer;
	initWriter(&writer, &ctrl);

	//ctrl.model = &model;
	/*for (int i = 0; i < 10; i++) {
		readToArray(&writer);
	}*/

//	PromptLoadDeck(&ctrl);

// Testing shuffles
    LoadDeckAtPath(&ctrl, "C:\\Users\\AGS17\\Desktop\\Yukon\\Decks\\UnshuffledDeck.txt");
    printf("Deck before shuffling:\n");
    PrintDeck(model.deck);
//	ll_node_card *shuffledDeck = shuffleInterleaving(&model.deck, 42);
    ll_node_card *shuffledDeck = shuffleRandom(&model.deck);
    printf("----------------------------------------------\n");
    printf("Deck after shuffling:\n");
    model.deck = shuffledDeck;
    PrintDeck(model.deck);
	return 0;
}
