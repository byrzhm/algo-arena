#include <bits/stdc++.h>

class Solution {
 public:
  int rob(std::vector<int> &nums) {
    if (nums.size() == 1) {
      return nums[0];
    }

    // dp[i] 表示只有前i间屋子时, 偷第i间屋子能偷窃到的最高总金额
    // dp[n] = max{dp[i]} ( 0<=i<=n-2 ) + nums[n]
    std::vector<int> dp(nums.size());
    dp[0] = nums[0];
    dp[1] = nums[1];

    int max = dp[0];
    for (int i = 2; i < nums.size(); ++i) {
      dp[i] = nums[i] + max;
      max = std::max(max, dp[i - 1]);
    }

    return std::max(dp[nums.size() - 1], dp[nums.size() - 2]);
  }
};