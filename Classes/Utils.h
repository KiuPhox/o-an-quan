#ifndef __UTILS_H__
#define __UTILS_H__

#include "GameObject/Stone.h"
#include "cocos2d.h"

class Utils
{
public:
	static int RandomRange(int min, int max) {
		return min + (rand() % (int)(max - min + 1));
	}
};

#endif // __UTILS_H__
