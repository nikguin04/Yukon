#include "printer.h"
#include "yukon_model.h"
#include <stdio.h>

void printYukonModel(YukonStructure *yukon, bool forceShow) { // NOTE: a flush of the cli is strongly recommended before using this is production
	ll_node_card *cur_card_ptr[NUM_COLUMNS];
	for (int i = 0; i < NUM_COLUMNS; i++) { // Print column headers
		printf("C%d\t", i + 1);
		cur_card_ptr[i] = yukon->columnFront[i];
	}
	printf("\n\n");
	PrintFoundationPiles(yukon);
	bool tailEmpty = false;
	int printedLines = 0;
	while (!tailEmpty) {
		tailEmpty = true;
		for (int i = 0; i < NUM_COLUMNS; i++) { // Print column headers
			if (cur_card_ptr[i] != NULL) {
				if (forceShow || !cur_card_ptr[i]->hidden) {
					char cardStr[3];
					CardToString(cur_card_ptr[i]->card, cardStr);
					printf("%s", cardStr);

				} else { printf("[]"); }
				tailEmpty = false;
				cur_card_ptr[i] = cur_card_ptr[i]->next;
			}
			printf("\t");
		}
		printf("\n");
		printedLines++;
	}
	for (int i = printedLines; i < NUM_FOUNDATIONS * 2 - 1; i++) {
		printf("\n");
	}
}

void PrintFoundationPiles(YukonStructure *yukon) {
	printf("%c7", '\x1B'); // DEC: save cursor position
	for (int i = 0; i < NUM_FOUNDATIONS; i++) {
		printf("%c[%d;%dH", '\x1B', 3 + 2 * i, 1 + 8 * NUM_COLUMNS); // Move to %d line and %d column (tab size times columns)
		char cardstr[3] = "[]";
		if (yukon->foundationPile[i] != NULL) { CardToString(yukon->foundationPile[i]->card, cardstr); }
		printf("%s F%d", cardstr, i + 1);
	}

	printf("%c8", '\x1B'); // DEC: load cursor position
}
