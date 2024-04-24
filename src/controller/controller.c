#include "controller.h"
#include <math.h>

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
	return "OK";
}

// y and height are relative to column card spacing
void GrabCard(Controller *ctrl, int source, float y, float height) {
	ctrl->model->yukon->activeMove = (ActiveMove) {};
	YukonStructure *yukon = ctrl->model->yukon;
	ll_node_card **from = NULL;
	ll_node_card *card;
	if (source > 0) {
		// Take from a column
		ll_node_card *prev = NULL;
		from = &yukon->columnFront[source - 1];
		card = *from;
		if (card == NULL) return;
		int i = 0;
		int index = (int) y;
		while (i != index && card->next != NULL) {
			prev = card;
			from = &card->next;
			card = *from;
			i++;
		}
		if (i != index && (int) floorf(y - height) >= i) return;
		ctrl->model->yukon->activeMove.cardToUnhide = prev;
		*from = NULL;
	} else {
		// Take from a foundation pile
		from = &yukon->foundationPile[-source - 1];
		card = *from;
		if (card == NULL) return;
		*from = card->next;
		card->next = NULL;
	}
	ctrl->model->yukon->activeMove.card = card;
	ctrl->model->yukon->activeMove.from = from;
	ctrl->model->yukon->activeMove.fromIsFoundation = source < 0;
}

const char *ValidateMove(Controller *ctrl, char destination, MoveDestination *result) {
	*result = (MoveDestination) {};
	YukonStructure *yukon = ctrl->model->yukon;
	ll_node_card **destPointer = NULL;
	if (destination > 0) {
		// Move to a column
		destPointer = &yukon->columnFront[destination - 1];
		ll_node_card *dest = *destPointer;
		if (dest == NULL) {
			if (yukon->activeMove.card->card.value != 13) return "Can only move a king to an empty column";
		} else {
			while (*(destPointer = &dest->next) != NULL) {
				dest = *destPointer;
			}
			if (dest->card.suit == yukon->activeMove.card->card.suit) return "Suits have to differ";
			if (dest->card.value - 1 != yukon->activeMove.card->card.value) return "Rank must be one lower";
		}
	} else {
		// Move to a foundation pile
		if (yukon->activeMove.card->next != NULL) return "Can only move one card to a foundation pile at a time";
		destPointer = &yukon->foundationPile[-destination - 1];
		if (*destPointer == NULL) {
			if (yukon->activeMove.card->card.value > 1) return "Can only move an ace to an empty foundation pile";
		} else {
			Card destCard = (*destPointer)->card;
			if (destCard.suit != yukon->activeMove.card->card.suit) return "Suits have to match";
			if (destCard.value + 1 != yukon->activeMove.card->card.value) return "Rank must be one higher";
		}
	}
	result->destPointer = destPointer;
	result->isFoundation = destination < 0;
	return "OK";
}

void CancelMove(Controller *ctrl) {
	ActiveMove *move = &ctrl->model->yukon->activeMove;
	if (!move->fromIsFoundation) {
		*move->from = move->card;
	} else {
		move->card->next = *move->from;
		*move->from = move->card;
	}
	move->card = NULL;
}

void CompleteMove(Controller *ctrl, MoveDestination dest) {
	ActiveMove *move = &ctrl->model->yukon->activeMove;
	if (move->cardToUnhide != NULL) {
		move->cardToUnhide->hidden = false;
	}
	if (dest.isFoundation) {
		move->card->next = *dest.destPointer;
	}
	*dest.destPointer = move->card;
}
