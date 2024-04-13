#include "printer.h"
#include "yukon_model.h"
#include <stdio.h>

void printYukonModel(YukonStructure *yukon, bool forceShow) { // NOTE: a flush of the cli is strongly recommended before using this is production
	ll_node_card *cur_card_ptr[COLUMN_SIZE];
	for (int i = 0; i < COLUMN_SIZE; i++) { // Print column headers
		printf("C%d\t", i);
		cur_card_ptr[i] = yukon->columnFront[i];
	}
	printf("\n");
	PrintFoundationPiles(yukon);
	if (cur_card_ptr[0] == NULL) { // This could be put above the C# printing, but we prefer it this way so the user knows it is empty
		return;
	}
	bool tailEmpty = false;
	while (!tailEmpty) {
		tailEmpty = true;
		for (int i = 0; i < COLUMN_SIZE; i++) { // Print column headers
			if (cur_card_ptr[i] != NULL) {
				if (forceShow || !cur_card_ptr[i]->card.hidden) {
					char cardStr[3];
					cardToString(&cur_card_ptr[i]->card, cardStr);
					printf("%s", cardStr);

				} else { printf("[]"); }
				tailEmpty = false;
				cur_card_ptr[i] = cur_card_ptr[i]->next;
			}
			printf("\t");
		}
		printf("\n");
	}

}

void PrintFoundationPiles(YukonStructure *yukon) {
	printf("%c7", '\x1B'); // DEC: save cursor position
	for (int i = 0; i < FOUNDATION_SIZE; i++) {
		printf("%c[%d;%dH", '\x1B', 2+2*i, 8*COLUMN_SIZE); // Move to %d line and %d column (tab size times columns)
			char cardstr[3] = "[]";
		if (yukon->foundationPile[i] != NULL) { cardToString(&yukon->foundationPile[i]->card, cardstr); }
		printf("%s\tF%d", cardstr, i+1);
	}


	printf("%c8", '\x1B'); // DEC: load cursor position
}
