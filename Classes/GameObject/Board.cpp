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

	this->isReady = true;
	this->isPause = false;

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
			stones->push_back(stone);
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
			stones->push_back(stone);
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

void Board::move(int index, bool clockwise, std::function<void()> callback) {
	if (index == 0 || index == 6) {
		callback();
		return;
	}

	int count = board[index];
	auto stones = getAllStoneInCell(index);
	board[index] = 0;


	while (count > 0) {
		index = getNextIndex(index, clockwise);
		setStonePosition(stones[count - 1], index, true);
		board[index]++;
		count--;
	}

	index = getNextIndex(index, clockwise);

	this->scheduleOnce([this, index, clockwise, callback](float dt) {
		if (board[index] > 0) {
			move(index, clockwise, callback);
		}
		else if (index != 0 && index != 6) {
			claim(getNextIndex(index, clockwise), clockwise, callback);
		}
		else {
			callback();
		}
	}, 1, "MOVE_OR_CLAIM");
}

void Board::claim(int index, bool clockwise, std::function<void()> callback) {
	if (board[index] == 0) {
		callback();
		return;
	}

	auto stones = getAllStoneInCell(index);

	for (auto stone : stones) {
		GameManager::addScore(stone->isBigStone ? 10 : 1);
		stone->setPosition(999, 999);
	}

	board[index] = 0;

	int nextIndex = getNextIndex(index, clockwise);
	if (board[nextIndex] > 0) {
		callback();
		return;
	}
	else {
		this->scheduleOnce([this, nextIndex, clockwise, callback](float dt) {
			claim(getNextIndex(nextIndex, clockwise), clockwise, callback);
			}
		, 1, "CLAIM");
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
	if (!this->isReady) return;
	if (this->isPause) return;

	int index = getCellIndex(position);

	auto playerTurn = GameManager::turn;

	if (this->selectedIndex == -1) {
		if (index == -1) return;

		if (board[index] > 0) {
			if (playerTurn == GameManager::PLAYER1 && !(index > 0 && index < 6)) return;
			if (playerTurn == GameManager::PLAYER2 && !(index > 6 && index < 12)) return;

			this->highlight->setVisible(true);
			this->highlight->setPosition(CELL_POSITION[index]);
			this->selectedIndex = index;
		}
	}
	else if (this->selectedIndex == index) {
		this->highlight->setVisible(false);
		this->selectedIndex = -1;
	}
	else {
		this->isReady = false;
		this->highlight->setVisible(false);

		bool left = position.x < CELL_POSITION[selectedIndex].x;

		if (GameManager::turn == GameManager::PLAYER2) {
			left = !left;
		}

		if (GameManager::OnPlayerMoveCallback != nullptr) {
			GameManager::OnPlayerMoveCallback(this->selectedIndex, left);
		}
		
		this->move(this->selectedIndex, left, [this]() {
			this->onMoveDone();
		});

		this->selectedIndex = -1;
	}
}

void Board::onMoveDone() {
	this->isReady = true;
	GameManager::changeTurn();

	if (!isMoveAvailable()) {
		this->scheduleOnce([](float dt) {
			GameManager::endGame();
		}, 0.2, "END_GAME");
	}
}

void Board::pause() {
	this->isPause = true;
}

void Board::resume() {
	this->isPause = false;
}

int Board::getCellIndex(Vec2 position) {
	for (int i = 0; i < 12; i++) {
		auto cellPosition = CELL_POSITION[i];
		if (isPositionInCell(position, i)) {
			return i;
		}
	}
	return -1;
}

bool Board::isMoveAvailable() {
	if (board[0] == 0 && board[6] == 0) return false;

	auto playerTurn = GameManager::turn;

	int startIndex = playerTurn == GameManager::PLAYER1 ? 1 : 7;
	int endIndex = playerTurn == GameManager::PLAYER1 ? 6 : 12;

	for (int i = startIndex; i < endIndex; i++) {
		if (board[i] > 0) {
			return true;
		}
	}

	return false;
}


std::vector<Stone*> Board::getAllStoneInCell(int index) {
	std::vector<Stone*> stones;
	for (auto stone : *this->stones) {
		if (isPositionInCell(stone->getPosition(), index)) {
			stones.push_back(stone);
		}
	}
	return stones;
}

bool Board::isPositionInCell(Vec2 position, int index) {
	auto cellPosition = CELL_POSITION[index];
	if (position.x >= cellPosition.x - CELL_SIZE / 2 && position.x <= cellPosition.x + CELL_SIZE / 2 &&
		position.y >= cellPosition.y - CELL_SIZE / 2 && position.y <= cellPosition.y + CELL_SIZE / 2) {
		return true;
	}
	return false;
}


