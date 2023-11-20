#include "State.h"
#include "Utils.h"

State::State(int board[12], int player, int player1_score, int player2_score)
    : player(player), player1_score(player1_score), player2_score(player2_score) {
    for (int i = 0; i < 12; ++i) {
		this->board[i] = board[i];
    }
}

std::vector<std::pair<int, bool>> State::get_possible_moves() {
    std::vector<std::pair<int, bool>> possible_move;

    if (player == 0) {
        for (int index = 0; index < 5; ++index) {
            if (board[index + 1] != 0) {
                possible_move.push_back(std::make_pair(index + 1, true));
            }
            if (board[index + 1] != 0) {
                possible_move.push_back(std::make_pair(index + 1, false));
            }
        }
    }
    else if (player == 1) {
        for (int index = 0; index < 5; ++index) {
            if (board[index + 7] != 0) {
                possible_move.push_back(std::make_pair(index + 7, true));
            }
            if (board[index + 7] != 0) {
                possible_move.push_back(std::make_pair(index + 7, false));
            }
        }
    }

    return possible_move;
}

int State::gap_score() {
    return player1_score - player2_score;
}

State* State::get_state(int index, bool is_clockwise) {
    int new_board[12];
    for (int i = 0; i < 12; ++i) {
		new_board[i] = board[i];
	}
    int score = Utils::move(new_board, index, is_clockwise);

    State* new_state = new State(
        new_board,
        (player == 0) ? 1 : 0,
        (player == 0) ? player1_score + score : player1_score,
        (player == 0) ? player2_score : player2_score + score
    );

    return new_state;
}