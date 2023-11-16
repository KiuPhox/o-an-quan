#include "GameManager.h"
#include "cocos2d.h"

GameManager::GameMode GameManager::mode = GameManager::GameMode::COMPUTER;
GameManager::PlayerTurn GameManager::turn = GameManager::PlayerTurn::PLAYER1;
int GameManager::playerId = 0;

std::function<void()> GameManager::OnTurnChangedCallback = nullptr;
std::function<void(int index, bool left)> GameManager::OnPlayerMoveCallback = nullptr;

void GameManager::changeTurn() {
	if (GameManager::turn == GameManager::PlayerTurn::PLAYER1) {
		GameManager::turn = GameManager::PlayerTurn::PLAYER2;
	}
	else {
		GameManager::turn = GameManager::PlayerTurn::PLAYER1;
	}

	if (GameManager::OnTurnChangedCallback != nullptr) {
		GameManager::OnTurnChangedCallback();
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