#ifndef MOVE_H
#define MOVE_H

#include "card.h"

// from == 0: Invalid input
// from/to > 0: Value is column index (starting at 1)
// from/to < 0: Absolute value is foundation pile (starting at 1)
// card.suit == 0: Only bottom-most card should be moved
// card.suit != 0: Indicates a specific card in the from-column
typedef struct MoveStruct {
	char from;
	char to;
	Card card;
} Move;

typedef struct ActiveMoveStruct {
	ll_node_card *card;
	ll_node_card **from;
	bool fromIsFoundation;
	char fromIndex;
	ll_node_card *cardToUnhide;
} ActiveMove;

typedef struct MoveDestinationStruct {
	ll_node_card **destPointer;
	bool isFoundation;
} MoveDestination;

#endif
