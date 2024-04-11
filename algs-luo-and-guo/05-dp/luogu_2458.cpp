#include <algorithm>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;  // 树中结点的数目
  std::cin >> n;

  std::vector<std::vector<int>> children(n + 1);
  std::vector<int> costs(n + 1);
  std::vector<int> parent(n + 1, -1);

  for (int p = 1; p <= n; ++p) {
    int i, cost, sonNum;
    std::cin >> i >> cost >> sonNum;
    costs[i] = cost;
    for (int q = 0; q < sonNum; ++q) {
      int j;
      std::cin >> j;
      children[i].emplace_back(j);
      parent[j] = i;
    }
  }

  int root = 1;
  while (parent[root] != -1)  // 获取根节点
    root = parent[root];

  auto dfs = [&](int root, auto &&dfs) -> std::tuple<int, int, int> {
    int by_self = costs[root], by_fa = 0, by_son = 0;
    int min_gap = std::numeric_limits<int>::max();
    bool flag   = false;
    for (auto child : children[root]) {
      auto [t_by_self, t_by_fa, t_by_son] = dfs(child, dfs);

      by_self += std::min(t_by_self, std::min(t_by_fa, t_by_son));
      by_fa   += std::min(t_by_self, t_by_son);
      by_son  += std::min(t_by_self, t_by_son);
      if (t_by_self > t_by_son) {
        by_son  += t_by_son;
        min_gap  = std::min(min_gap, t_by_self - t_by_son);
      } else {
        flag    = true;
        by_son += t_by_self;
      }
    }

    if (!flag) {
      by_son += min_gap;
    }

    return {by_self, by_fa, by_son};
  };

  auto [by_self, _, by_son] = dfs(root, dfs);
  std::cout << std::max(by_self, by_son) << '\n';

  return 0;
}