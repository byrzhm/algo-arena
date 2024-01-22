#include <bits/stdc++.h>

class Solution {
 public:
  bool canPartition(const std::vector<int> &nums) {
    int sum = std::accumulate(nums.begin(), nums.end(), 0);

    if ((sum & 0x1) != 0) {
      return false;
    }

    int target = sum >> 1;

    // 物品价值与重量相等
    // dp[i][j] 表示背包大小为 j 时, 装前 i 个物品得到的最大价值
    std::vector<std::vector<int>> dp(nums.size() + 1, std::vector<int>(target + 1, 0));
    for (int i = 1; i <= nums.size(); ++i) {
      for (int j = 1; j <= target; ++j) {  // j 为背包大小
        if (j >= nums[i - 1]) {
          dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - nums[i - 1]] + nums[i - 1]);
        } else {
          dp[i][j] = dp[i - 1][j];
        }
      }
    }

    return dp[nums.size()][target] == target;  // 正好能装满一半
  }
};

int main() { std::cout << Solution().canPartition({1, 5, 11, 5}) << std::endl; }