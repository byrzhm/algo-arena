#include <bits/stdc++.h>

class Solution {
 public:
  int coinChange(std::vector<int> &coins, int amount) {
    if (amount == 0) {
      return 0;
    }

    std::sort(coins.begin(), coins.end());
    std::vector<int> dp(amount + 1);
    dp[0] = 0;

    for (int i = 1; i <= amount; ++i) {
      dp[i] = -1;
      for (int coin : coins) {
        if (i - coin < 0) {
          break;
        }

        if (dp[i - coin] >= 0) {
          dp[i] = (dp[i] == -1) ? dp[i - coin] + 1 : std::min(dp[i - coin] + 1, dp[i]);
        }
      }
    }
    return dp[amount];
  }
};