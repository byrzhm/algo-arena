#include <vector>

// clang-format off
class Solution {
 public:
  int minPathSum(std::vector<std::vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();
    std::vector<std::vector<int>> dp(m, std::vector<int>(n));

    dp[0][0] = grid[0][0];
    for (int i = 1; i < m; ++i) dp[i][0] = grid[i][0] + dp[i - 1][0];
    for (int j = 1; j < n; ++j) dp[0][j] = grid[0][j] + dp[0][j - 1];

    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
      }
    }
    return dp[m - 1][n - 1];
  }
};
// clang-format on
