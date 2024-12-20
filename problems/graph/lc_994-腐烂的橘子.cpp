#include <bits/stdc++.h>

struct Node {
  int timestamp;
  int row;
  int col;
  explicit Node(int timestamp = 0, int row = 0, int col = 0) : timestamp(timestamp), row(row), col(col) {}
};

class Solution {
 public:
  int orangesRotting(std::vector<std::vector<int>> &grid) {
    r = grid.size();
    c = grid[0].size();
    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
        if (grid[i][j] == 2) {
          queue.emplace(0, i, j);
          ++rotten_count;
        } else if (grid[i][j] == 1) {
          ++fresh_count;
        }

    return bfs(grid);
  }

 private:
  int bfs(std::vector<std::vector<int>> &grid) {
    int ans = -1;
    Node node;
    while (!queue.empty()) {
      node = queue.front();
      queue.pop();

      int row = node.row;
      int col = node.col;
      int timestamp = node.timestamp;

      try_rotting(grid, row - 1, col, timestamp + 1);
      try_rotting(grid, row + 1, col, timestamp + 1);
      try_rotting(grid, row, col - 1, timestamp + 1);
      try_rotting(grid, row, col + 1, timestamp + 1);
    }
    if (fresh_count == 0) {
      ans = node.timestamp;
    }
    return ans;
  }

  void try_rotting(std::vector<std::vector<int>> &grid, int row, int col, int timestamp) {
    if (row >= 0 && row < r && col >= 0 && col < c && grid[row][col] == 1) {
      grid[row][col] = 2;
      queue.emplace(timestamp, row, col);
      --fresh_count;
      ++rotten_count;
    }
  }

 private:
  std::queue<Node> queue;
  int fresh_count;
  int rotten_count;
  int r;  ///< grid 行数
  int c;  ///< grid 列数
};