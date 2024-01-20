#include <bits/stdc++.h>

/**
 * 25 -> 1
 * 25 == 16 + 9
 */
class Solution {
 public:
  int numSquares(int n) {
    if (n == 1) {
      return 1;
    }

    std::vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
      int root = static_cast<int>(std::sqrt(i));
      dp[i] = dp[i - 1] + 1;
      for (int d = root; d > 0; --d) {
        if (dp[i] > dp[i - d * d] + 1) {
          dp[i] = dp[i - d * d] + 1;
          if (dp[i] == 1) {
            break;
          }
        }
      }
    }
    return dp[n];
  }
};

// 四平方和定理