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

	static std::vector<std::string> split(std::string str, std::string delimiter) {
		std::vector<std::string> result;
		size_t pos = 0;
		std::string token;
		while ((pos = str.find(delimiter)) != std::string::npos) {
			token = str.substr(0, pos);
			result.push_back(token);
			str.erase(0, pos + delimiter.length());
		}
		result.push_back(str);
		return result;
	}
};

#endif // __UTILS_H__
