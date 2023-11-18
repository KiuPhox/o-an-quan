#include "Stone.h"

USING_NS_CC;

Stone::Stone(bool isBigStone) {
	auto sprite = Sprite::create("stone.png");
	this->isBigStone = isBigStone;
	if (isBigStone) {
		sprite->setScale(2);
	}
	this->addChild(sprite);
}