#include <bits/stdc++.h>

class Solution {
 public:
  int numIslands(std::vector<std::vector<char>> &grid) {
    int row = grid.size();
    int col = grid[0].size();
    int size = row * col;
    int zeros = size;
    init(size);

    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < col; ++j) {
        if (grid[i][j] == '1') {
          grid[i][j] = '0';  // 小技巧
          --zeros;
          if (i - 1 >= 0 && grid[i - 1][j] == '1') {
            union_set(i * col + j, (i - 1) * col + j);
          }
          if (j - 1 >= 0 && grid[i][j - 1] == '1') {
            union_set(i * col + j, i * col + j - 1);
          }
          if (i + 1 < row && grid[i + 1][j] == '1') {
            union_set(i * col + j, (i + 1) * col + j);
          }
          if (j + 1 < col && grid[i][j + 1] == '1') {
            union_set(i * col + j, i * col + j + 1);
          }
        }
      }
    }

    return count_sets(0, size) - zeros;
  }

 private:
  void init(int size) {
    rank.resize(size, 0);
    parent.resize(size);
    for (int i = 0; i < size; i++) {
      parent[i] = i;
    }
  }

  bool connected(int x, int y) { return find_set(x) == find_set(y); }

  int find_set(int x) {
    int old = x;
    int ancestor = parent[x];
    while (ancestor != x) {
      x = ancestor;
      ancestor = parent[x];
    }
    x = parent[old];
    while (ancestor != x) {
      parent[old] = ancestor;
      old = x;
      x = parent[old];
    }
    return ancestor;
  }

  void link(int x, int y) {
    if (x == y) return;

    if (rank[x] > rank[y])
      parent[y] = x;
    else {
      parent[x] = y;
      if (rank[x] == rank[y]) ++rank[y];
    }
  }

  void union_set(int x, int y) { link(find_set(x), find_set(y)); }

  int count_sets(int first, int last) {
    int count = 0;
    for (; first != last; ++first) {
      if (parent[first] == first) {
        ++count;
      }
    }
    return count;
  }

 private:
  std::vector<int> rank;
  std::vector<int> parent;
};