#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>

class Utils
{
public:
	static int claim(int board[12], int index, bool clockwise) {
		if (board[index] == 0) {
			return 0;
		}
		int count = board[index];
		board[index] = 0;

		int nextIndex = getNextIndex(index, clockwise);
		if (board[nextIndex] > 0) {
			return count;
		}
		else {
			return count + claim(board, getNextIndex(nextIndex, clockwise), clockwise);
		}
	}

	static int move(int board[12], int index, bool clockwise) {
		int new_board[12];
		for (int i = 0; i < 12; ++i) {
			new_board[i] = board[i];
		}

		if (index == 0 || index == 6) {
			return 0;
		}

		int count = 0;

		if (new_board[index] / 1000 == 1) {
			count += 10;
			new_board[index] -= 1000;
			return 0;
		}

		count += new_board[index] ;
		new_board[index] = 0;


		while (count > 0) {
			index = getNextIndex(index, clockwise);
			new_board[index]++;
			count--;
		}

		index = getNextIndex(index, clockwise);

		if (new_board[index] > 0) {
			return move(new_board, index, clockwise);
		}
		else if (index != 0 && index != 6) {
			return claim(new_board, getNextIndex(index, clockwise), clockwise);
		}
		else {
			return 0;
		}
	}

	static int getNextIndex(int index, bool clockwise) {
		int nextIndex = clockwise ? index - 1 : index + 1;
		if (nextIndex < 0) {
			nextIndex = 11;
		}
		else if (nextIndex > 11) {
			nextIndex = 0;
		}
		return nextIndex;
	}
};
#endif // __UTILS_H__