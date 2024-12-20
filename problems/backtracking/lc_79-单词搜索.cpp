#include <bits/stdc++.h>

class Solution {
 public:
  bool exist(std::vector<std::vector<char>> &board, const std::string &word) {
    r = board.size();
    c = board[0].size();
    found = false;
    search_start_points(board, word);

    while (!found && !start_points.empty()) {
      auto [row, col] = start_points.back();
      visited[index_of(row, col)] = true;
      backtrack(board, word, row, col, 1);
      visited[index_of(row, col)] = false;
      start_points.pop_back();
    }

    return found;
  }

 private:
  bool valid_index(int row, int col) { return (row < r && row >= 0) && (col < c && col >= 0); }

  int index_of(int row, int col) { return row * c + col; }

  void backtrack(std::vector<std::vector<char>> &board, const std::string &word, int row, int col, int step) {
    // std::cout << row << ": " << col << std::endl;

    if (step == word.size()) {
      found = true;
      return;
    }

    auto validator = [&](int _row, int _col) {
      return !found && valid_index(_row, _col) && word[step] == board[_row][_col] && !visited[index_of(_row, _col)];
    };

    // Left
    if (validator(row, col - 1)) {
      visited[index_of(row, col - 1)] = true;
      backtrack(board, word, row, col - 1, step + 1);
      visited[index_of(row, col - 1)] = false;
    }

    // Right
    if (validator(row, col + 1)) {
      visited[index_of(row, col + 1)] = true;
      backtrack(board, word, row, col + 1, step + 1);
      visited[index_of(row, col + 1)] = false;
    }

    // Up
    if (validator(row + 1, col)) {
      visited[index_of(row + 1, col)] = true;
      backtrack(board, word, row + 1, col, step + 1);
      visited[index_of(row + 1, col)] = false;
    }

    // Down
    if (validator(row - 1, col)) {
      visited[index_of(row - 1, col)] = true;
      backtrack(board, word, row - 1, col, step + 1);
      visited[index_of(row - 1, col)] = false;
    }
  }

  void search_start_points(std::vector<std::vector<char>> &board, const std::string &word) {
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        if (board[i][j] == word[0]) {
          start_points.emplace_back(i, j);
        }
      }
    }
  }

 private:
  bool found;
  int r;
  int c;
  std::vector<std::pair<int, int>> start_points;
  std::unordered_map<int, bool> visited;
};