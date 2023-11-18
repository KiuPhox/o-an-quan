#ifndef __STONE_H__
#define __STONE_H__

#include "cocos2d.h"

class Stone : public cocos2d::Sprite
{
private:
public:
	Stone(bool isBigStone = false);

	bool isBigStone;
};

#endif // __STONE_H__
