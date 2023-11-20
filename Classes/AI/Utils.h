#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>

class Utils
{
public:
	static int capture(std::vector<int>& board, int index, bool is_clockwise) {
        int rotation = (is_clockwise) ? 1 : -1;
        int offset = 0;
        int capture_score = 0;

        while (true) {
            int index1 = (index + rotation * (offset + 1)) % 12;
            if (index1 < 0) {
				index1 += 12;
			}
        
            if (board[index1] != 0) {
                break;
            }
            int index2 = (index + rotation * (offset + 2)) % 12;

            if (index2 < 0) {
                index2 += 12;
            }
            if (board[index2] != 0) {
                capture_score += board[index2];
                board[index2] = 0;
            }
            else {
                break;
            }

            offset += 2;
        }

        return capture_score;
    }

    static std::pair<int, int> single_move(std::vector<int>& board, int index, bool is_clockwise) {
        int rotation = (is_clockwise) ? 1 : -1;
        if (index < 0) {
            index += 12;
        }
        int total_stone = board[index];

        if (index == 0 || index == 6) {
            if (board[index] / 1000 == 1) {
                return std::make_pair(index, -1);
            }
        }
        else if (total_stone == 0) {
            return std::make_pair(index, -1);
        }

        board[index] = 0;

        for (int stone = 0; stone < total_stone; ++stone) {
            int i = (index + rotation * (1 + stone)) % 12;
            if (i < 0) {
               i += 12;
            }
            board[i] += 1;
        }

        int current_index = index;
        int next_index = (index + rotation * (total_stone)) % 12;

        return std::make_pair(current_index, next_index);
    }

    static int move(std::vector<int>& board, int index, bool is_clockwise) {
        int next_index = index;
        std::vector<std::pair<int, int>> list_move;

        while (true) {
            auto pair = single_move(board, next_index, is_clockwise);
            auto current_index = pair.first;
            auto new_next_index = pair.second;
            list_move.push_back(std::make_pair(current_index, new_next_index));

            if (new_next_index == -1 || new_next_index == 0 || new_next_index == 6) {
                if ((new_next_index == 0 || new_next_index == 6) && board[new_next_index] / 1000 == 0) {
                    continue;
                }
                break;
            }

            next_index = new_next_index;
        }

        int score;
        if (list_move.back().second != -1) {
            score = capture(board, list_move.back().first, is_clockwise);
        }
        else {
            int index = list_move.size() - 2;
            if (index < 0) {
				index += list_move.size();
			}
            score = capture(board, list_move[index].first, is_clockwise);
        }

        return score;
    }
};

#endif // __UTILS_H__
