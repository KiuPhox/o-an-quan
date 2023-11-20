#ifndef __BOARD_H__
#define __BOARD_H__

#include "cocos2d.h"
#include "Stone.h"

#include <vector>

class Board : public cocos2d::Sprite
{
private:
	std::vector<Stone*> stones[52];
	int getNextIndex(int index, bool clockwise);
	bool isReady;
	bool isPause;
public:
	Board();

	int board[12];

	cocos2d::Sprite *highlight;
	int selectedIndex = -1;

	void move(int index, bool clockwise, std::function<void()> callback);
	void claim(int index, bool clockwise, std::function<void()> callback);
	void setStonePosition(Stone* stone, int index, bool animate = false);
	void onMouseDown(cocos2d::Vec2 position);
	void onMoveDone();

	void pause();
	void resume();
	
	bool isMoveAvailable();

	int getCellIndex(cocos2d::Vec2 position);
	bool isPositionInCell(cocos2d::Vec2 position, int index);

	std::vector<Stone*> getAllStoneInCell(int index);
	
};

#endif // __BOARD_H__
