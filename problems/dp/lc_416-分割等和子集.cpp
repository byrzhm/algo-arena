#include <algorithm>
#include <bitset>
#include <iostream>
#include <numeric>
#include <vector>

namespace dp1 {

class Solution
{
public:
  bool canPartition(const std::vector<int> &nums)
  {
    int n = nums.size();
    if (n < 2) {
      return false;
    }

    int sum = std::accumulate(nums.begin(), nums.end(), 0);

    if ((sum & 0x1) != 0) {
      return false;
    }

    int target = sum >> 1;

    // 物品价值与重量相等
    // dp[i][j] 表示背包大小为 j 时, 装前 i 个物品得到的最大价值
    std::vector<std::vector<int>> dp(nums.size() + 1, std::vector<int>(target + 1, 0));
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= target; ++j) {  // j 为背包大小
        if (j >= nums[i - 1]) {
          dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - nums[i - 1]] + nums[i - 1]);
        } else {
          dp[i][j] = dp[i - 1][j];
        }
      }
    }

    return dp[n][target] == target;  // 正好能装满一半
  }
};

}  // namespace dp1

namespace dp2 {

class Solution
{
public:
  bool canPartition(const std::vector<int> &nums)
  {
    int n = nums.size();
    if (n < 2) {
      return false;
    }

    int sum = std::accumulate(nums.begin(), nums.end(), 0);

    // 不是偶数
    if ((sum & 0x1) != 0) {
      return false;
    }

    int target = sum >> 1;

    // 物品价值与重量相等
    // dp[i][j] 表示背包大小为 j 时, 装前 i 个物品得到的最大价值
    std::vector<std::vector<bool>> dp(nums.size() + 1, std::vector<bool>(target + 1, false));
    dp[0][0] = true;
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= target; ++j) {  // j 为背包大小
        if (j >= nums[i - 1]) {
          dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
        } else {
          dp[i][j] = dp[i - 1][j];
        }
      }
    }

    return dp[n][target];
  }
};

}  // namespace dp2

namespace dp3 {

class Solution
{
public:
  bool canPartition(const std::vector<int> &nums)
  {
    int n = nums.size();
    if (n < 2) {
      return false;
    }

    int sum = std::accumulate(nums.begin(), nums.end(), 0);

    // 不是偶数
    if ((sum & 0x1) != 0) {
      return false;
    }

    int target = sum >> 1;

    std::vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (auto num : nums) {
      for (int j = target; j >= num; --j) {
        dp[j] = dp[j] || dp[j - num];
      }
    }
    return dp[target];
  }
};

}  // namespace dp3

namespace dp4 {

class Solution
{
public:
  bool canPartition(const std::vector<int> &nums)
  {
    //why 10001? cover all the cases of sum of subarr 100 * 200 / 2 = 10000
    std::bitset<10001> f;
    int sum = 0;
    f[0]    = true;
    for (int num : nums) {
      f    = f << num | f; // 直接消去一个 for 循环
      sum += num;
    }
    if ((sum & 1) != 0) {
      return false;
    }
    return f[sum >> 1];
  }
};

}  // namespace dp4


int main()
{
  std::cout << dp1::Solution().canPartition({1, 5, 11, 5}) << '\n';
  std::cout << dp2::Solution().canPartition({1, 5, 11, 5}) << '\n';
  std::cout << dp3::Solution().canPartition({1, 5, 11, 5}) << '\n';
  std::cout << dp4::Solution().canPartition({1, 5, 11, 5}) << '\n';
}