#include "GameManager.h"
#include "cocos2d.h"

GameManager::GameMode GameManager::mode = GameManager::GameMode::COMPUTER;
GameManager::PlayerTurn GameManager::turn = GameManager::PlayerTurn::PLAYER1;

int GameManager::playerId = 0;
int GameManager::player1Score = 0;
int GameManager::player2Score = 0;

std::function<void()> GameManager::OnUIChangedCallback = nullptr;
std::function<void(int index, bool left)> GameManager::OnPlayerMoveCallback = nullptr;

void GameManager::changeTurn() {
	if (GameManager::turn == GameManager::PlayerTurn::PLAYER1) {
		GameManager::turn = GameManager::PlayerTurn::PLAYER2;
	}
	else {
		GameManager::turn = GameManager::PlayerTurn::PLAYER1;
	}

	if (GameManager::OnUIChangedCallback != nullptr) {
		GameManager::OnUIChangedCallback();
	}
}

bool GameManager::isPlayerTurn() {
	if (mode == GameMode::COMPUTER) {
		return turn == PlayerTurn::PLAYER1;
	}
	else {
		return turn == playerId - 1;
	}
}

void GameManager::addScore(int score) {
	if (turn == PlayerTurn::PLAYER1) {
		player1Score += score;
	}
	else {
		player2Score += score;
	}

	if (GameManager::OnUIChangedCallback != nullptr) {
		GameManager::OnUIChangedCallback();
	}
}