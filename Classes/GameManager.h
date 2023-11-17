#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <functional>

class GameManager
{
public:
    enum GameMode {
        PLAYER,
        COMPUTER
    };

    enum PlayerTurn {
		PLAYER1,
		PLAYER2
	};

    static GameMode mode;
    static PlayerTurn turn;
    static int playerId;

    static int player1Score;
    static int player2Score;

    static bool isPlayerTurn();
    static void changeTurn();
    static void addScore(int score);

    static void endGame();

    static std::function<void()> OnUIChangedCallback;
    static std::function<void(int index, bool left)> OnPlayerMoveCallback;
};

#endif // __GAME_MANAGER_H__
