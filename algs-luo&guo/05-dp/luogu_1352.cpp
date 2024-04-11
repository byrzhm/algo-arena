#include <iostream>
#include <utility>
#include <vector>

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> r(n);
  for (int i = 0; i < n; ++i)
    std::cin >> r[i];
  
  std::vector<std::vector<int>> digraph(n);
  std::vector<int> parent(n, -1);
  for (int i = 0; i < n - 1; ++i) {
    int l, k;
    std::cin >> l >> k;
    --l, --k;
    digraph[k].emplace_back(l);
    parent[l] = k;
  }

  int root = 0;
  while (parent[root] != -1) {
    root = parent[root];
  }

  auto dfs = [&](int i, auto &&dfs) -> std::pair<int, int> {
    int x = r[i], xn = 0;
    for (const auto &j : digraph[i]) {
      auto [t, tn]  = dfs(j, dfs);
      x            += tn;
      xn           += std::max(t, tn);
    }

    return {x, xn};
  };

  auto [x, xn] = dfs(root, dfs);
  std::cout << std::max(x, xn) << '\n';
  return 0;
}