#include <bits/stdc++.h>

namespace solution1 {

/**
 * !使用最长公共子序列计算最长严格单调递增子序列不是最优解
 */
class Solution {
 public:
  int lengthOfLIS(std::vector<int> &nums) {
    std::vector<int> copy = nums;
    std::sort(copy.begin(), copy.end());
    auto last = std::unique(copy.begin(), copy.end());
    copy.erase(last, copy.end());
    return LCSLength(nums, copy);
  }

  int LCSLength(const std::vector<int> &x, const std::vector<int> &y) {
    int m = x.size();
    int n = y.size();

    std::vector<std::vector<int>> c(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (x[i - 1] == y[j - 1]) {
          c[i][j] = c[i - 1][j - 1] + 1;
        } else {
          c[i][j] = std::max(c[i - 1][j], c[i][j - 1]);
        }
      }
    }

    return c[m][n];
  }
};

} // namespace solution1

namespace solution2 {

class Solution {
 public:
  int lengthOfLIS(std::vector<int> &nums) { return {
  }; }
};

} // namespace solution2 