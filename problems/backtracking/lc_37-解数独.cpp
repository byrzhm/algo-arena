#include <bits/stdc++.h>

class SudokuSolver {
public:
  void solve(std::vector<std::vector<char>>& board) {
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(blk, 0, sizeof(blk));

    valid = false;

    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (board[i][j] == '.') {
          spaces.emplace_back(i, j);
        } else {
          int digit = board[i][j] - '0' - 1;
          row[i][digit] = col[j][digit] = blk[i / 3][j / 3][digit] = true;
        }
      }
    }
    
    backtracking(board, 0);
  }
  
private:
  void backtracking(std::vector<std::vector<char>> &board, int step) {
    if (step == spaces.size()) {
      valid = true;
      return;
    }

    auto [i, j] = spaces[step];
    for (int digit = 0; digit < 9 && !valid; ++digit) {
      if (!row[i][digit] && !col[j][digit] && !blk[i / 3][j / 3][digit]) {
        row[i][digit] = col[j][digit] = blk[i / 3][j / 3][digit] = true;
        board[i][j] = digit + '0' + 1;
        backtracking(board, step + 1);
        row[i][digit] = col[j][digit] = blk[i / 3][j / 3][digit] = false;
      }
    }
  }

private:
  std::vector<std::pair<int, int>> spaces;
  bool row[9][9];
  bool col[9][9];
  bool blk[3][3][9];
  bool valid;
};

