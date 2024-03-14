#include <algorithm>
// #include <cstdio>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

namespace binary_search {

class Solution
{
public:
  int splitArray(std::vector<int> &nums, int k)
  {
    // 最大值为 mid
    // 如果划分数目非常小，说明mid值很大
    // 如果划分数目非常大，说明mid值很小
    // 希望 mid 值越来越小
    auto checkFn = [&](long long mid) {
      long long sum = 0;
      int count     = 1;
      for (auto num : nums) {
        if (sum + num > mid) {
          ++count;
          sum = 0;
        }
        sum += num;
      }
      return count <= k;
    };

    long long sum = std::accumulate(nums.begin(), nums.end(), 0LL);
    long long l   = *std::max_element(nums.begin(), nums.end());
    long long r   = sum;

    while (l < r) {
      long long mid = (l + r) >> 1;
      if (checkFn(mid)) {  // 划分数目很小，说明 mid 值很大
        r = mid;
      } else {             // 划分数目很大，说明 mid 值很小
        l = mid + 1;
      }
    }

    return l;
  }
};

}  // namespace binary_search

namespace dp {

/*

「将数组分割为 m 段，求……」是动态规划题目常见的问法。

令 f[i][j] 表示将数组的前 j 个数分割为 i 段所能得到的最大连续子数组和的最小值。
在进行状态转移时，我们可以考虑第 i 段的具体范围，即我们可以枚举 k，其中前 k 个数
被分割为 i−1 段，而第 k+1 到第 j 个数为第 i 段。此时，这 i 段子数组中和的最大值，
就等于 f[i-1][k-1] 与 sub(k, j) 中的较大值，其中 sub(i, j) 表示数组 nums 中
下标落在区间 [i,j] 内的数的和。

由于我们要使得子数组中和的最大值最小，因此可以列出如下的状态转移方程：

f[i][j] = min_{k=i}^{j}(max(f[i-1][k-1], sub(k, j)))

*/

class Solution
{
public:
  int splitArray(std::vector<int> &nums, int m)
  {
    int n = nums.size();
    std::vector<std::vector<int>> f(m + 1, std::vector<int>(n + 1, std::numeric_limits<int>::max()));
    std::vector<int> sum(n + 1);
    for (int i = 1; i <= n; ++i) {
      sum[i] = nums[i - 1] + sum[i - 1];
    }
    f[0][0] = 0;                              // f[0][0] 初始化为 0，其余初始化为 +inf 才能正确的转移
    for (int i = 1; i <= m; ++i) {
      for (int j = i; j <= n + i - m; ++j) {  // 前 j 个数分成 i 段, 后 n-j 个数分成 m-i 段, i <= j <= n+i-m
        for (int k = i; k <= j; ++k) {        // 枚举第 i 段的左端点
          f[i][j] = std::min(std::max(f[i - 1][k - 1], sum[j] - sum[k - 1]), f[i][j]);
        }
      }
    }

    // printf("m=%d n=%d\n", m, n);
    // for (int i = 0; i <= m; ++i) {
    //   for (int j = 0; j <= n; ++j) {
    //     std::cout << f[i][j] << ' ';
    //   }
    //   std::cout << '\n';
    // }
    return f[m][n];
  }
};

}  // namespace dp

int main()
{
  std::vector<int> nums{7, 2, 5, 10, 8};
  int m = 2;
  std::cout << dp::Solution().splitArray(nums, m) << '\n';
}