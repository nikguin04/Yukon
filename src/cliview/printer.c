#include "printer.h"

void print_yukon_model(YukonStructure *yukon, bool force_show) { // NOTE: a flush of the cli is strongly recommended before using this is production
    ll_node_card *cur_card_ptr[COLUMN_SIZE];
    for (int i = 0; i < COLUMN_SIZE; i++) { // Print column headers
        printf("C%d\t",i);
        cur_card_ptr[i] = yukon->Column_FRONT[i];
    }
    printf("\n");
    bool tailEmpty = false;
    while (!tailEmpty) {
        tailEmpty = true;
        for (int i = 0; i < COLUMN_SIZE; i++) { // Print column headers
            if (cur_card_ptr[i]) { // not null
                if (force_show || !cur_card_ptr[i]->card.hidden) {
                    char cardStr[3]; cardToString(&cur_card_ptr[i]->card, cardStr);
                    printf("%s", cardStr);
                    
                }
                else {printf("[]");}
                tailEmpty = false;
                cur_card_ptr[i] = cur_card_ptr[i]->next;
            }
            printf("\t");
        }
        printf("\n");
    }
}


