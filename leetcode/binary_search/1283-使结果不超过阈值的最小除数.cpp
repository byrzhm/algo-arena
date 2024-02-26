#include <algorithm>
#include <cstdint>
#include <numeric>
#include <vector>

/*

给你一个整数数组 nums 和一个正整数 threshold，
你需要选择一个正整数作为除数，然后将数组里每个数都除以它，并对除法结果求和。

请你找出能够使上述结果小于等于阈值 threshold 的除数中 最小 的那个。

每个数除以除数后都向上取整，比方说 7/3 = 3 ， 10/2 = 5 。

! 除数越大，结果越小，越可能小于等于阈值
! 使用二分法

*/

class Solution
{
public:
  int smallestDivisor(std::vector<int> &nums, int threshold)
  {
    auto checkFn = [&](int divisor) {
      int64_t res = std::accumulate(nums.begin(), nums.end(), 0LL, [&](int64_t current, int num) {
        return current + (num - 1) / divisor + 1;
      });
      return res <= threshold;
    };

    int l = 1;
    // int r = std::numeric_limits<int>::max();
    int r = *std::max_element(nums.begin(), nums.end());

    while (l < r) {
      // int mid = l + ((r - l) >> 1);
      int mid = (l + r) >> 1;
      if (checkFn(mid)) { // 结果小于等于阈值
        r = mid;
      } else { // 结果大于阈值
        l = mid + 1;
      }
    }

    return l;
  }
};
