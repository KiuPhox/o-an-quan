#ifndef __ALPHA_H__
#define __ALPHA_H__

#include "State.h"
#include <map>

const int MAX_DEPTH = 4;

class Alpha
{
public:
    std::vector<std::pair<State*, std::vector<std::pair<int, std::pair<int, bool>>>>> visited_states;

	int calculate_score(State* state) {
		return state->gap_score();
	}

	bool is_visited(State* state, int depth) {
        for (const auto& visited : visited_states) {
            if (visited.first == state) {
                if (depth < visited.second.size() && visited.second[depth].first != -1) {
                    return true;
                }
                break;
            }
        }
        return false;
	}

	void add_visited_state(State* state, int depth, const std::pair<int, bool>& action, int score) {
        for (auto& visited : visited_states) {
            if (visited.first == state) {
                if (depth >= visited.second.size()) {
                    visited.second.resize(depth + 1, std::make_pair(-1, std::make_pair(0, false)));
                }
                visited.second[depth] = std::make_pair(score, action);
                return;
            }
        }
        visited_states.emplace_back(state, std::vector<std::pair<int, std::pair<int, bool>>>(depth + 1, std::make_pair(-1, std::make_pair(0, false))));
        visited_states.back().second[depth] = std::make_pair(score, action);
	}

    std::pair<std::pair<int, bool>, int> minimax(State* state, int depth, int alpha, int beta) {
        if (depth == 0) {
            return std::make_pair(std::make_pair(-1, false), calculate_score(state));
        }

        if (is_visited(state, depth)) {
            for (const auto& visited : visited_states) {
                if (visited.first == state) {
                    auto v = visited.second[depth];
                    auto score = v.first;
                    auto action = v.second;
                    return std::make_pair(action, score);
                }
            }
        }

        auto possible_moves = state->get_possible_moves();
        std::pair<std::pair<int, bool>, int> best_action = std::make_pair(std::make_pair(-1, false), 0);

        if (state->player == 1) {
            int max_value = -10000;
            for (const auto& move : possible_moves) {
                auto possible_move = move.first;
                auto direction = move.second;

                auto next_move = std::make_pair(possible_move, direction);
                auto next_state = state->get_state(possible_move, direction);

                auto m = minimax(next_state, depth - 1, alpha, beta);
                auto action = m.first;
                auto value = m.second;

                add_visited_state(next_state, depth - 1, action, value);

                if (value > max_value) {
                    max_value = value;
                    best_action = std::make_pair(next_move, max_value);
                }

                alpha = std::max(alpha, max_value);
                if (beta <= alpha) {
                    break;
                }
            }
            return best_action;
        }
        else {
            int min_value = 10000;
            for (const auto& move : possible_moves) {
                auto possible_move = move.first;
                auto direction = move.second;
                auto next_move = std::make_pair(possible_move, direction);

                auto next_state = state->get_state(possible_move, direction);

                auto m = minimax(next_state, depth - 1, alpha, beta);
                auto action = m.first;
                auto value = m.second;
                add_visited_state(next_state, depth - 1, action, value);

                if (value < min_value) {
                    min_value = value;
                    best_action = std::make_pair(next_move, min_value);
                }

                beta = std::min(beta, min_value);
                if (beta <= alpha) {
                    break;
                }
            }
            return best_action;
        }
    }

    std::pair<int, bool> minimax_move(State* state) {
        auto m = minimax(state, MAX_DEPTH, -10000, 10000);
        auto action = m.first;
        return action;
    }
public:
	
};

#endif // __ALPHA_H__
