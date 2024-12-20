#include <iostream>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// O(n^m) very slow
namespace bruteforce {

class Solution
{
public:
  int earliestSecondToMarkIndices(std::vector<int> &nums, std::vector<int> &changeIndices)
  {
    n = nums.size();
    m = changeIndices.size();

    backtracking(nums, changeIndices, 1);

    return valid ? minTime : -1;
  }

private:
  void backtracking(std::vector<int> &nums, std::vector<int> &changeIndices, int second)
  {
    int s = second - 1;

    if (marked.size() == n) {
      valid   = true;
      minTime = std::min(minTime, s);
    }

    if (s >= m || s >= minTime) {
      return;
    }

    // mark
    if (nums[changeIndices[s] - 1] == 0 && marked.count(changeIndices[s]) == 0) {
      marked.insert(changeIndices[s]);
      backtracking(nums, changeIndices, second + 1);
      marked.erase(changeIndices[s]);
    }

    // -1
    for (int i = 0; i < n; ++i) {
      if (nums[i] > 0) {
        --nums[i];
        backtracking(nums, changeIndices, second + 1);
        ++nums[i];
      }
    }

    // do nothing
    backtracking(nums, changeIndices, second + 1);
  }

  static constexpr auto INF = std::numeric_limits<int>::max();

  int n;
  int m;
  int minTime = INF;
  bool valid  = false;
  std::unordered_set<int> marked;
};

}  // namespace bruteforce

namespace binary_search {

/**
 * 假设有 n 门课程，第 i 门课程需要 nums[i] 天复习
 * 并不是每天都可以选择一门课考试, 在第 k 天可以考第 changeIndices[k] 门课程
 *  
 * nums = [2,2,0], changeIndices = [2,2,2,2,3,2,2,1]
 *   有三门课程，分别需要 2，2，0 天时间复习
 *   在第1-4，6-7天可以考第二门课程，在第5天可以考第三门课程，在第8天可以考第一门课程
 *
 * ! 时间越长越容易完成, 单调性满足, 尝试二分
 */
class Solution
{
public:
  int earliestSecondToMarkIndices(std::vector<int> &nums, std::vector<int> &changeIndices)
  {
    int n = nums.size();
    int m = changeIndices.size();
    std::unordered_map<int, int> lastDay;  // lastDay[i] 第 i 门课可以考试的最后一天, (i in [0, n - 1])

    auto checkFn = [&](int days) {
      lastDay.clear();
      for (int i = 0; i < days; ++i) {
        int idx      = changeIndices[i] - 1;
        lastDay[idx] = i;       // 记录可以考试的最后一天
      }

      if (lastDay.size() != n)  // 在指定的时间内不能考完所有的课程
        return false;

      int count = 0;
      for (int i = 0; i < days; ++i) {
        int idx = changeIndices[i] - 1;  // 第 i 天可以考第 idx 门课程
        if (i == lastDay[idx]) {         // 如果是该课程可以考试的最后一天, 必须考试
          if (nums[idx] > count)         // 如果复习的时间不够, 说明在限定的时间内无法考完全部课程
            return false;
          count -= nums[idx];            // 复习的时间减去 nums[idx]
        } else {
          ++count;                       // 不是可以考试的最后一天, 复习的时间加一天
        }
      }

      return true; // 在规定的时间内考完了全部的课程
    };

    int l = 1, r = m + 1;

    while (l < r) {
      int mid = (l + r) >> 1;
      if (checkFn(mid)) { // mid 天可以考完
        r = mid;
      } else { // mid 天无法考完
        l = mid + 1;
      }
    }

    return l > m ? -1 : l;
  }
};

}  // namespace binary_search

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // [0,8,4,7,10,7,6,0,3,6]
  // [5,3,6,2,6,6,10,4,6]
  std::vector<int> nums          = {0, 8, 4, 7, 10, 7, 6, 0, 3, 6};
  std::vector<int> changeIndices = {5, 3, 6, 2, 6, 6, 10, 4, 6};
  std::cout << bruteforce::Solution().earliestSecondToMarkIndices(nums, changeIndices) << '\n';

  return 0;
}