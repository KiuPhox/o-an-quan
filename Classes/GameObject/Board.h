#ifndef __BOARD_H__
#define __BOARD_H__

#include "cocos2d.h"

class Board
{
private:
	int board[12];

	int getNextIndex(int index, bool left);
public:
	Board();

	void move(int index, bool left);
	void claim(int index, bool left);
};

#endif // __BOARD_H__
