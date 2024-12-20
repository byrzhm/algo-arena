/**
 * Buy Low Sell High
 * https://codeforces.com/problemset/problem/865/D
 */

#include <functional>
#include <iostream>
#include <queue>
#include <vector>

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::priority_queue<int, std::vector<int>, std::greater<>> options;

  int64_t ans = 0;

  for (int i = 0; i < n; ++i) {
    int price;
    std::cin >> price;
    if (!options.empty() && options.top() < price) {
      ans += price - options.top();
      options.pop();
      options.push(price);  // 关键在于 push 两次
                            // 一次等价于取消卖出
                            // 另一次作为买入处理
    }
    options.push(price);
  }

  std::cout << ans << '\n';

  return 0;
}