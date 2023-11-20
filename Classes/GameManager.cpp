#include "GameManager.h"
#include "cocos2d.h"

GameManager::GameMode GameManager::mode = GameManager::GameMode::COMPUTER;
GameManager::PlayerTurn GameManager::turn = GameManager::PlayerTurn::PLAYER1;

int GameManager::playerId = 0;
int GameManager::player1Score = 0;
int GameManager::player2Score = 0;

std::function<void()> GameManager::OnTurnChangedCallback = nullptr;
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

void GameManager::endGame() {
	if (playerId == 1 || mode == GameMode::COMPUTER) {
		if (player1Score > player2Score) {
			cocos2d::ccMessageBox("You Win!", "Game Over");
		}
		else if (player1Score < player2Score) {
			cocos2d::ccMessageBox("You Lose!", "Game Over");
		}
		else {
			cocos2d::ccMessageBox("Draw!", "Game Over");
		}
	}
	else if (playerId == 2){
		if (player1Score > player2Score) {
			cocos2d::ccMessageBox("You Lose!", "Game Over");
		}
		else if (player1Score < player2Score) {
			cocos2d::ccMessageBox("You Win!", "Game Over");
		}
		else {
			cocos2d::ccMessageBox("Draw!", "Game Over");
		}
	}

	cocos2d::Director::getInstance()->end();
}