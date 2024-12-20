#include <climits>
#include <iostream>
#include <vector>

/*

前缀和 s[i + 1] = num[0] + nums[1] + ... + nums[i]
定义 f[i][j] 表示从 nums[0] 到 nums[j−1] 中选出 i 个不相交非空连续子数组的最大能量值。

- 不选 nums[j - 1] 问题变成从前 j - 1 个数中选 i 个不相交的子数组: f[i][j] = f[i][j - 1]
- 选 nums[j - 1] 作为第 i 段子数组的右端点, 枚举第 i 个子数组最左元素的下标, 记作 L
    那么第 i 段子数组的元素和为 nums[L] + nums[L + 1] + ... + nums[j - 1] = s[j] - s[L]
    前面还剩下 L 个数, f[i][j] = f[i - 1][L] + (s[j] - s[L]) * w, w = (-1)^(i + 1) * (k - i + 1)
    L 不能小于 i - 1, 因为前面的 i - 1 个子数组，每个都至少要有 1 个元素

f[i][j] = max(f[i][j - 1], {l <- i-1..j-1}max{f[i - 1][l] + (s[j] - s[l]) * w})

f[i][j] = max(f[i][j - 1], s[j] * w + max{f[i - 1][l]  - s[l] * w})

j <- i ...
f[i][i]     : l <- i - 1
f[i][i + 1] : l <- i - 1, i
f[i][i + 2] : l <- i - 1, i, i + 1

*/

namespace bruteforce {

class Solution
{
public:
  long long maximumStrength(std::vector<int> &nums, int k)
  {
    int n = nums.size();
    std::vector<long long> s(n + 1);
    for (int i = 0; i < n; i++) {
      s[i + 1] = s[i] + nums[i];
    }

    std::vector<std::vector<long long>> f(k + 1, std::vector<long long>(n + 1));
    for (int i = 1; i <= k; ++i) {
      int w       = ((i % 2) == 0 ? -1 : 1) * (k - i + 1);
      f[i][i - 1] = LLONG_MIN;
      for (int j = i; j <= n - k + i; ++j) {
        f[i][j] = f[i][j - 1];
        for (int l = i - 1; l <= j - 1; ++l) {
          f[i][j] = std::max(f[i][j], f[i - 1][l] + (s[j] - s[l]) * w);
        }
      }
    }
    return f[k][n];
  }
};

}  // namespace bruteforce

namespace normal {

class Solution
{
public:
  long long maximumStrength(std::vector<int> &nums, int k)
  {
    int n = nums.size();
    std::vector<long long> s(n + 1);
    for (int i = 0; i < n; i++) {
      s[i + 1] = s[i] + nums[i];
    }

    std::vector<std::vector<long long>> f(k + 1, std::vector<long long>(n + 1));
    for (int i = 1; i <= k; ++i) {
      f[i][i - 1]   = LLONG_MIN;
      long long max = LLONG_MIN;
      int w         = (k - i + 1) * ((i % 2) != 0 ? 1 : -1);
      for (int j = i; j <= n - k + i; ++j) {
        max     = std::max(max, f[i - 1][j - 1] - s[j - 1] * w);
        f[i][j] = std::max(f[i][j - 1], s[j] * w + max);
      }
    }
    return f[k][n];
  }
};

}  // namespace normal

namespace optimal {

class Solution
{
public:
  long long maximumStrength(std::vector<int> &nums, int k)
  {
    int n = nums.size();
    std::vector<long long> s(n + 1);
    for (int i = 0; i < n; i++) {
      s[i + 1] = s[i] + nums[i];
    }
    std::vector<long long> f(n + 1);
    for (int i = 1; i <= k; i++) {
      long long pre = f[i - 1];
      f[i - 1]      = LLONG_MIN;
      long long mx  = LLONG_MIN;
      int w         = (k - i + 1) * ((i % 2) != 0 ? 1 : -1);
      for (int j = i; j <= n - k + i; j++) {
        mx   = std::max(mx, pre - s[j - 1] * w);
        pre  = f[j];
        f[j] = std::max(f[j - 1], s[j] * w + mx);
      }
    }
    return f[n];
  }
};

}  // namespace optimal

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // nums = [-100000000,-10000000,123,234]
  std::vector<int> nums{-100000000, -10000000, 123, 234};
  int k = 3;

  std::cout << bruteforce::Solution().maximumStrength(nums, k) << '\n';
  std::cout << normal::Solution().maximumStrength(nums, k) << '\n';
  std::cout << optimal::Solution().maximumStrength(nums, k) << '\n';

  return 0;
}