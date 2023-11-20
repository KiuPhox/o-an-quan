#include "State.h"
#include "Utils.h"

State::State(std::vector<int> board, int player, int player1_score, int player2_score)
    : board(board), player(player), player1_score(player1_score), player2_score(player2_score) {}

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
    std::vector<int> new_board = board;  // Assuming move function is correctly implemented
    int score = Utils::move(new_board, index, is_clockwise);

    State* new_state = new State(
        new_board,
        (player == 0) ? 1 : 0,
        (player == 0) ? player1_score + score : player1_score,
        (player == 0) ? player2_score : player2_score + score
    );

    return new_state;
}