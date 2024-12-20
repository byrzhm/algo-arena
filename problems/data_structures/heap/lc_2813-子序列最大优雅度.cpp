#include <algorithm>
#include <cstdint>
#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>

/*

- 如果选出的 item 数少于 k，那么只需要无脑选就行
- 如果已经选出了 k 个，遇到新的我们应该是否应该进行替换?

按照 profit 进行排序
先选前 k 个。
遇到新的，如果是已经出现的类别，一定不会使总利润增加
如果是未出现的新类别，可能使得总利润增加，并且一旦增加，就必须要将其替换
   我们永远不会替换前面只出现一次的类别

*/

class Solution
{
public:
  long long findMaximumElegance(std::vector<std::vector<int>> &items, int k)
  {
    // 按照 profit 进行排序
    std::sort(items.begin(), items.end(), [](std::vector<int> &item1, std::vector<int> &item2) {
      return item1.front() > item2.front();
    });

    int64_t total_profit = 0;
    int64_t ans          = 0;

    std::unordered_set<int> set;
    std::stack<int> duplicate;

    // 前 k 个 item
    for (int i = 0; i < k; ++i) {
      int profit    = items[i].front();
      int category  = items[i].back();
      total_profit += profit;
      if (!set.insert(category).second) {  // 重复类别
        duplicate.emplace(profit);
      }
    }

    ans = total_profit + set.size() * set.size();

    // 后面的 item
    for (int i = k; i < items.size(); ++i) {
      int profit   = items[i].front();
      int category = items[i].back();

      // 如果第一次出现该类别, 找到前面最后重复出现的类别
      if (!duplicate.empty() && set.insert(category).second) {
        total_profit -= duplicate.top() - profit;
        duplicate.pop();
      }

      // 大致来说 total_profit + distinct_categories**2 会是一个先下降后上升的过程
      // 中间可能有波动, 因为我们的 total_profit 变小了，但是 distinct_categories 变大了
      ans = std::max(ans, total_profit + static_cast<int64_t>(set.size()) * static_cast<int64_t>(set.size()));
    }

    return ans;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // [[3,2],[5,1],[10,1]]
  std::vector<std::vector<int>> items{
    {3, 2},
    {5, 1},
    {10, 1}
  };

  int k = 2;

  std::cout << Solution().findMaximumElegance(items, k) << '\n';

  return 0;
}