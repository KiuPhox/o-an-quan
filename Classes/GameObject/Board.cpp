#include "Board.h"
#include "Utils.h"
#include "GameManager.h"

USING_NS_CC;

const int CELL_SIZE = 130;
const Vec2 CELL_POSITION[12] = {
	Vec2(225, 364),
	Vec2(360, 290),
	Vec2(496, 290),
	Vec2(632, 290),
	Vec2(768, 290),
	Vec2(904, 290),
	Vec2(1045, 364),
	Vec2(904, 430),
	Vec2(768, 430),
	Vec2(632, 430),
	Vec2(496, 430),	
	Vec2(360, 430),
};

Board::Board() {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto sprite = this->create("bg.png");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite, 0);

	this->highlight = Sprite::create("highlight.png");
	this->highlight->setVisible(false);
	this->addChild(this->highlight, 1);

	for (int i = 0; i < 12; i++) {
		board[i] = 5;
	}

	for (int i = 0; i < 52; i++) {
		if (i == 0 || i == 26) {
			auto stone = new Stone(true);
			stone->setPosition(Vec2(rand() % (int)visibleSize.width, rand() % (int)visibleSize.height));
			this->addChild(stone, 1);

			if (i == 0) {
				setStonePosition(stone, 0, true);
			}
			else {
				setStonePosition(stone, 6, true);
			}
		}
		else {
			auto stone = new Stone(false);
			stone->setPosition(Vec2(rand() % (int)visibleSize.width, rand() % (int)visibleSize.height));
			this->addChild(stone, 1);

			if (i < 26) {
				setStonePosition(stone, (i - 1) / 5 + 1, true);
			}
			else if (i > 26) {
				setStonePosition(stone, (i - 2) / 5 + 2, true);
			}
		}
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

void Board::setStonePosition(Stone* stone, int index, bool animate) {
	auto cellPosition = CELL_POSITION[index];
	auto cellSize = CELL_SIZE - 30;
	auto randomInCell = Vec2(Utils::RandomRange(-cellSize / 2, cellSize / 2),
		Utils::RandomRange(-cellSize / 2, cellSize / 2));

	if (animate) {
		auto move = MoveTo::create(1, cellPosition + randomInCell);
		stone->runAction(move);
	}
	else {
		stone->setPosition(cellPosition + randomInCell);
	}
}

void Board::onMouseDown(Vec2 position){
	int index = getCellIndex(position);

	if (index == 0 || index == 6 || index == -1) return;

	auto playerTurn = GameManager::turn;

	if (playerTurn == GameManager::PLAYER1 && !(index > 0 && index < 6)) return;
	if (playerTurn == GameManager::PLAYER2 && !(index > 6 && index < 12)) return;

	if (board[index] > 0) {
		this->highlight->setVisible(true);
		this->highlight->setPosition(CELL_POSITION[index]);
	}
}

int Board::getCellIndex(Vec2 position) {
	for (int i = 0; i < 12; i++) {
		auto cellPosition = CELL_POSITION[i];
		if (position.x >= cellPosition.x - CELL_SIZE / 2 && position.x <= cellPosition.x + CELL_SIZE / 2 &&
			position.y >= cellPosition.y - CELL_SIZE / 2 && position.y <= cellPosition.y + CELL_SIZE / 2) {
			return i;
		}
	}
	return -1;
}