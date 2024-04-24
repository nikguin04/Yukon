#include "controller.h"

void initController(Controller *ctrl, Model *model) {
	ctrl->model = model;
}

const char *PerformMove(Controller *ctrl, Move move) {
	YukonStructure *yukon = ctrl->model->yukon;
	// I hope you like pointers
	ll_node_card *prev = NULL;
	ll_node_card *node;
	ll_node_card **destPointer = NULL;
	// -------------------------------------------
	//  Information gathering and move validation
	// -------------------------------------------
	if (move.from == move.to) return "Can't move from and to the same place";
	if (move.from > 0) {
		// Card is in a column
		node = yukon->columnFront[move.from - 1];
		if (node == NULL) return "Can't move from empty column";
		if (move.card.suit == 0) {
			// No card specified, so use the last one
			while (node->next != NULL) {
				prev = node;
				node = node->next;
			}
		} else {
			// Look for a specific card
			while (!CardEquals(node->card, move.card)) {
				prev = node;
				node = node->next;
				if (node == NULL) return "Couldn't find that card in that column";
			}
			// If the card is there, but hidden, pretend it wasn't found
			if (node->hidden) return "Couldn't find that card in that column";
		}
	} else {
		// Card is in a foundation pile
		node = yukon->foundationPile[-move.from - 1];
		if (node == NULL) return "Can't move from empty foundation pile";
	}
	if (move.to > 0) {
		// Move to column
		destPointer = &yukon->columnFront[move.to - 1];
		ll_node_card *dest = *destPointer;
		if (dest == NULL) {
			if (node->card.value != 13) return "Can only move a king to an empty column";
		} else {
			while (*(destPointer = &dest->next) != NULL) {
				dest = *destPointer;
			}
			if (dest->card.suit == node->card.suit) return "Suits have to differ";
			if (dest->card.value - 1 != node->card.value) return "Rank must be one lower";
		}
	} else {
		// Move to foundation
		if (move.from > 0 && node->next != NULL) return "Can only move one card to a foundation pile at a time";
		destPointer = &yukon->foundationPile[-move.to - 1];
		if (*destPointer == NULL) {
			if (node->card.value > 1) return "Can only move an ace to an empty foundation pile";
		} else {
			Card destCard = (*destPointer)->card;
			if (destCard.suit != node->card.suit) return "Suits have to match";
			if (destCard.value + 1 != node->card.value) return "Rank must be one higher";
		}
	}
	// ------------------------------
	//  Actually performing the move
	// ------------------------------
	// This is done afterwards to make sure the move is completely valid before actually changing anything,
	// so we don't do half a move operation, which could result in memory leaks, lost cards... just general nightmares...
	if (move.from > 0) {
		if (prev == NULL) {
			yukon->columnFront[move.from - 1] = NULL;
		} else {
			prev->next = NULL;
			prev->hidden = false;
		}
	} else {
		yukon->foundationPile[-move.from - 1] = node->next;
		node->next = NULL;
	}
	if (move.to < 0) {
		node->next = *destPointer;
	}
	*destPointer = node;

    for (int i = 0; i < NUM_FOUNDATIONS; i++) {
        if (yukon->foundationPile[i] == NULL) {
            break;
        }
        if (yukon->foundationPile[i]->card.value != 13) {
            break;
        }
        if (i == NUM_FOUNDATIONS - 1) {
            return "YOU WIN!";
        }
    }
	return "OK";
}
