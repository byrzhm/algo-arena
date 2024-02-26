#include <functional>
#include <iostream>
#include <queue>
#include <vector>

/**
 * 输入：heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
 * 输出：4
 * 解释：从建筑物 0 出发，你可以按此方案完成旅程：
 * - 不使用砖块或梯子到达建筑物 1 ，因为 4 >= 2
 * - 使用 5 个砖块到达建筑物 2 。你必须使用砖块或梯子，因为 2 < 7
 * - 不使用砖块或梯子到达建筑物 3 ，因为 7 >= 6
 * - 使用唯一的梯子到达建筑物 4 。你必须使用砖块或梯子，因为 6 < 9
 * 无法越过建筑物 4 ，因为没有更多砖块或梯子。
 */


namespace binary_search {

/*

单调性：越远越难抵达，越近越容易抵达
! 可以使用二分法

* check: 先决定在什么地方放梯子
? 如何选择在何处放梯子 - 贪心反悔

*/

class Solution
{
public:
  int furthestBuilding(std::vector<int> &heights, int bricks, int ladders)
  {
    using MinHeap = std::priority_queue<int, std::vector<int>, std::greater<>>;

    int n         = heights.size();
    std::vector<int> diffVec(n - 1);
    for (int i = 0; i < n - 1; ++i) {
      diffVec[i] = heights[i + 1] - heights[i];
    }

    auto checkFn = [&](int dst) {
      MinHeap heap;
      int laddersHave = ladders;
      int bricksNeed  = 0;
      for (int i = 0; i < dst; ++i) {
        int diff = diffVec[i];
        if (diff <= 0) {  // 没有必要使用砖头或梯子
          continue;
        }

        if (laddersHave == 0) {                      // 没有梯子可以用了，尝试反悔，把梯子用在该用的地方
          if (heap.empty() || heap.top() >= diff) {  // 无法反悔
                                                     // 要么根本没有梯子，要么反悔会使得结果更糟
            bricksNeed += diff;                      // 需要 diff 块砖头
            continue;
          }

          // 选择反悔

          bricksNeed += heap.top();  // 改用砖头
          ++laddersHave;
          heap.pop();
        }
        --laddersHave;
        heap.emplace(diff);
      }

      return bricks >= bricksNeed;
    };

    int l = 0;
    int r = n - 1;

    while (l < r) {
      int mid = (l + r + 1) >> 1;
      if (checkFn(mid)) {  // mid 可以抵达
        l = mid;
      } else {             // mid 不可抵达
        r = mid - 1;
      }
    }

    return l;
  }
};

}  // namespace binary_search

namespace one_pass {

class Solution
{
public:
  int furthestBuilding(std::vector<int> &heights, int bricks, int ladders)
  {
    using MaxHeap = std::priority_queue<int, std::vector<int>, std::less<>>;
    MaxHeap heap;
    int n = heights.size();
    for (int i = 1; i < n; ++i) {
      int diff = heights[i] - heights[i - 1];
      if (diff <= 0)
        continue;

      if (diff <= bricks) {                          // 砖头够，优先使用砖头
        bricks -= diff;
        heap.emplace(diff);
      } else {                                       // 砖头不够，尝试反悔, 使用梯子
        if (ladders > 0) {                           // 如果有梯子
          if (!heap.empty() && heap.top() > diff) {  // 当前位置diff更小，使用砖头会更好
            bricks += heap.top();
            bricks -= diff;
            heap.pop();
            heap.push(diff);
          }
          // 如果反悔了，那么在前面使用梯子
          // 如果未反悔，在当前位置使用梯子
          --ladders;  // 消耗一个梯子
        } else {      // 没有梯子，无法反悔
          return i - 1;
        }
      }
    }
    return n - 1;
  }
};

}  // namespace one_pass


int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<int> heights{4, 2, 7, 6, 9, 14, 12};
  int bricks  = 5;
  int ladders = 1;

  std::cout << binary_search::Solution().furthestBuilding(heights, bricks, ladders) << '\n';
  std::cout << one_pass::Solution().furthestBuilding(heights, bricks, ladders) << '\n';

  return 0;
}