#include <vector>

class Solution
{
public:
  int sumOfPower(std::vector<int> &nums, int k)
  {
    constexpr auto MOD = 1'000'000'007;
    std::vector<int> dp(k + 1, 0);
    dp[0] = 1;
    for (int num : nums) {
      for (int j = k; j >= 0; --j) {
        if (j >= num) {
          dp[j] = ((dp[j] << 1) + dp[j - num]) % MOD;
        } else {
          dp[j] = (dp[j] << 1) % MOD;
        }
      }
    }
    return dp[k];
  }
};