#ifndef MOVE_H
#define MOVE_H

#include "card.h"

// from == 0: Invalid input
// from/to > 0: Value is column index (starting at 1)
// from/to < 0: Absolute value is foundation pile (starting at 1)
// fromCardValue == 0: Only bottom-most card should be moved
// fromCardValue > 0: Indicates a specific card in the from-column along with fromCardSuit
typedef struct MoveStruct {
	char from;
	char to;
	char fromCardValue;
	CardSuit fromCardSuit;
} Move;

#endif
