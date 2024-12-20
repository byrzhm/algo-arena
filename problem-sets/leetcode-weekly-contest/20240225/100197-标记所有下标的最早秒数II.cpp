#include <functional>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

/**
 * 假设有 n 门课程，第 i 门课程需要 nums[i] 天复习
 * ! 每天都可以选择一门课考试
 * ! 在第 k 天可以突击复习第 changeIndices[k] 门课程, (立即复习完)
 * 
 * nums = [3,2,3], changeIndices = [1,3,2,2,2,2,3]
 *   有三门课程，正常情况下分别需要 3，2，3 天时间复习, 现在允许突击复习
 * * 在第一天突击复习第一门课程，第二天突击复习第三门课程，第三天突击复习第二门课程
 * * 然后花三天时间考试, 最早6天可以考完所有课程
 *
 * ! 时间越长越容易完成, 单调性满足, 尝试二分
 */
class Solution
{
public:
  int earliestSecondToMarkIndices(std::vector<int> &nums, std::vector<int> &changeIndices)
  {
    int n  = nums.size();
    int m  = changeIndices.size();

    std::unordered_map<int, int> firstDay;  // firstDay[i] 第 i 门课的第一次突击复习时间
    for (int i = m - 1; i >= 0; --i) {
      int idx       = changeIndices[i] - 1;
      firstDay[idx] = i;
    }

    auto checkFn = [&](int days) {
      using Pair = std::pair<int, int>;
      std::priority_queue<Pair, std::vector<Pair>, std::greater<>> heap;
      std::unordered_set<int> done;
      // if (days < n)
      //   return false;

      // 先考虑突击复习
      // - 执行突击复习，消耗一天来考试
      // - 不突击复习的情况：
      //    1，nums[i] = 0
      //    2，nums[i] = 1
      //    3，count = 0 不能突击复习
      //       ! 但是可以反悔

      int count = 0;                                 // 剩余正常复习或考试的时间
      for (int i = days - 1; i >= 0; --i) {
        int idx = changeIndices[i] - 1;              // 第 idx 门课程可以被突击复习
        if (nums[idx] <= 1 || i != firstDay[idx]) {  // 需要的复习时间少于1天，并且不是可以突击复习的第一天
          ++count;                                   // 留给前面，复习或考试
          continue;
        }

        // nums[idx] > 1 && i == firstDay[idx]
        // 需要的复习时间大于 1 天，并且是可以突击复习的第一天

        if (count == 0) {                                       // 无法突击复习，尝试反悔
          if (heap.empty() || nums[idx] <= heap.top().first) {  // 🙅无法反悔，没有突击复习了并考完的课程
                                                                // 或者反悔使用突击复习会更糟
            ++count;                                            // 留给前面，复习或考试
            continue;
          }

          // 之前有突击复习并考完的课程
          // 或者反悔使用突击复习会更好
          // ! 可以进行反悔
          done.erase(heap.top().second);
          count += 2;  // 一次考试，一次突击复习
        }

        done.insert(idx);
        --count;  // 置0后，消耗一次考试的时间
        heap.emplace(nums[idx], idx);
      }

      for (int i = 0; i < n; ++i) {
        if (done.count(i) == 0) {
          count -= nums[i] + 1;  // 正常复习的时间，以及考试的时间
        }
        if (count < 0) return false;
      }

      return true;
    };

    int l = n, r = m + 1;

    while (l < r) {
      int mid = (l + r) >> 1;
      if (checkFn(mid)) {  // 可以在规定的时间内考完
        r = mid;
      } else {             // 不可以在规定的时间内考完
        l = mid + 1;
      }
    }

    return l > m ? -1 : l;
  }
};