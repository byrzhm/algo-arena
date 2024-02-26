#include <iostream>
#include <vector>

/**
 * 给你一个整数数组 citations ，其中 citations[i] 表示研究者的第 i 篇论文被引用的次数，
 * citations 已经按照 升序排列 。计算并返回该研究者的 h 指数。
 *
 * h 指数的定义：h 代表“高引用次数”（high citations），一名科研人员的 h 指数是指他（她）的
 * （n 篇论文中）至少 有 h 篇论文分别被引用了至少 h 次。
 */


/**
 * @brief 在引用次数确定的情况下, 先猜 h 指数，
 * 如果猜的大，那么越难符合要求，如果猜的小，那么要求越容易满足
 */
class Solution
{
public:
  int hIndex(std::vector<int> &citations)
  {
    int n = citations.size();

    // auto checkFn = [&](int hIdx) {
    //   int count = n;
    //   for (auto cite : citations) {
    //     if (cite < hIdx)
    //       --count;
    //   }
    //   return count >= hIdx;
    // };

    auto checkFn = [&](int hIdx) {
      return hIdx == 0 || citations[n - hIdx] >= hIdx;
    };


    int l = 0, r = n;

    while (l < r) {
      int mid = (l + r + 1) >> 1;
      if (checkFn(mid)) {  // 满足 h 指数的要求
        l = mid;
      } else {             // 不满足 h 指数的要求
        r = mid - 1;
      }
    }

    return l;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<int> citations{0, 1, 3, 5, 6};
  std::cout << Solution().hIndex(citations) << '\n';

  return 0;
}