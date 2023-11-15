#include "GameManager.h"
#include "cocos2d.h"

GameManager::GameMode GameManager::mode = GameManager::GameMode::COMPUTER;
GameManager::PlayerTurn GameManager::turn = GameManager::PlayerTurn::PLAYER1;
std::function<void()> GameManager::OnTurnChangedCallback = nullptr;

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