#include "Stone.h"

USING_NS_CC;

Stone::Stone(bool isBigStone) {
	auto sprite = Sprite::create("stone.png");
	if (isBigStone) {
		sprite->setScale(2);
	}
	this->addChild(sprite);
}