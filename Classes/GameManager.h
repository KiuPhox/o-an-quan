#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

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
};

#endif // __GAME_MANAGER_H__
