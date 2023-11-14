#ifndef __BOARD_H__
#define __BOARD_H__

#include "cocos2d.h"
#include "Stone.h"

class Board : public cocos2d::Sprite
{
private:
	int board[12];
	int getNextIndex(int index, bool left);
public:
	Board();

	cocos2d::Sprite *highlight;

	void move(int index, bool left);
	void claim(int index, bool left);
	void setStonePosition(Stone* stone, int index, bool animate = false);
	void onMouseDown(cocos2d::Vec2 position);
	int getCellIndex(cocos2d::Vec2 position);
};

#endif // __BOARD_H__
