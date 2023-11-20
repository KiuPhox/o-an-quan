#ifndef __STATE_H__
#define __STATE_H__

#include <vector>

class State
{
public:
	std::vector<int> board;
	int player;
	int player1_score;
	int player2_score;

	State(std::vector<int> board, int player, int player1_score, int player2_score);

	std::vector<std::pair<int, bool>> get_possible_moves();
	int gap_score();

	State* get_state(int index, bool clockwise);
};



#endif // __STATE_H__
