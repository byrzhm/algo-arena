#include <bits/stdc++.h>

namespace sol1 {

class Solution {
 public:
  int uniquePaths(int m, int n) {
    std::vector<std::vector<int>> dp(m, std::vector<int>(n));
    for (int i = 0; i < m; ++i) dp[i][0] = 1;
    for (int j = 0; j < n; ++j) dp[0][j] = 1;

    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
      }
    }
    return dp[m - 1][n - 1];
  }
};

}  // namespace sol1

namespace sol2 {

/**
 * 向下移动 m - 1 次, 向右移动 n - 1 次
 * 从 m + n - 2 次移动中选出 m - 1 次向下的移动即可
 * C(m + n - 2, m - 1) = (m + n - 2)! / ((m - 1)! (n - 1)!)
 */
class Solution {
 public:
  int uniquePaths(int m, int n) {
    uint64_t ans = 1;
    for (int x = n, y = 1; y < m; ++x, ++y) ans = ans * x / y;
    return ans;
  }
};

}  // namespace sol2