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

    static bool isPlayerTurn();
    static void changeTurn();

    static std::function<void()> OnTurnChangedCallback;
    static std::function<void(int index, bool left)> OnPlayerMoveCallback;
};

#endif // __GAME_MANAGER_H__
