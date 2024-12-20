#include <vector>

class Solution
{
public:
  int countSubmatrices(std::vector<std::vector<int>> &grid, int k)
  {
    int r = grid.size();
    int c = grid[0].size();
    std::vector<std::vector<int>> sum(r + 1, std::vector<int>(c + 1, 0));

    int count = 0;

    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        sum[i + 1][j + 1] = grid[i + 1][j + 1] + sum[i][j + 1] + sum[i + 1][j] - sum[i][j];
        if (sum[i + 1][j + 1] <= k)
          ++count;
      }
    }

    return count;
  }
};