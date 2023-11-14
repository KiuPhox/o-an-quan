#include "Board.h"

Board::Board() {
	for (int i = 0; i < 12; i++) {
		board[i] = 5;
	}
}

int Board::getNextIndex(int index, bool left) {
	int nextIndex = left ? index - 1 : index + 1;
	if (nextIndex < 0) {
		nextIndex = 11;
	}
	else if (nextIndex > 11) {
		nextIndex = 0;
	}
	return nextIndex;
}

void Board::move(int index, bool left) {
	int count = board[index];
	board[index] = 0;

	while (count > 0) {
		index = getNextIndex(index, left);
		board[index]++;
		count--;
	}

	if (board[index] > 0) {
		move(index, left);
	}
	else {
		claim(getNextIndex(index, left), left);
	}
}

void Board::claim(int index, bool left) {
	board[index] = 0;

	int nextIndex = getNextIndex(index, left);
	if (board[nextIndex] > 0) {
		return;
	}
	else {
		claim(getNextIndex(nextIndex, left), left);
	}
}