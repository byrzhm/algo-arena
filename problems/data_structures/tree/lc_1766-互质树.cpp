#include <functional>
#include <numeric>
#include <utility>
#include <vector>
using std::function;
using std::gcd;
using std::pair;
using std::vector;

class Solution
{
public:
  static constexpr auto MAX = 50;

  vector<vector<int>> prepare()
  {
    vector<vector<int>> coprimes(MAX + 1);
    for (int i = 1; i <= MAX; ++i)
      for (int j = 1; j <= MAX; ++j)
        if (gcd(i, j) == 1)
          coprimes[i].emplace_back(j);

    return coprimes;
  }

  vector<int> getCoprimes(vector<int> &nums, vector<vector<int>> &edges)
  {
    int n         = nums.size();
    auto coprimes = prepare();
    vector<vector<int>> adj(n);
    for (const auto &edge : edges) {
      int u = edge.front(), v = edge.back();
      adj[u].emplace_back(v);
      adj[v].emplace_back(u);
    }

    vector<int> ans(n, -1);
    vector<pair<int, int>> cache(MAX + 1, {-1, -1});

    function<void(int, int, int)> dfs = [&](int i, int fa, int depth) {
      int val       = nums[i];
      int max_depth = -1;
      for (const auto &x : coprimes[val]) {
        if (cache[x].first > max_depth) {
          max_depth = cache[x].first;
          ans[i]    = cache[x].second;
        }
      }

      auto save  = cache[val];
      cache[val] = {depth, i};

      for (const auto &j : adj[i])
        if (j != fa)
          dfs(j, i, depth + 1);

      cache[val] = save;
    };

    dfs(0, -1, 0);

    return ans;
  }
};