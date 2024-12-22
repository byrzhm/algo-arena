#include <algorithm>
#include <unordered_map>
#include <vector>

// clang-format off
class Solution
{
  std::unordered_map<int, int> power_map {{1, 0}};
public:
  void dfs(int x) {
    if (power_map.contains(x)) return;
    if (x % 2 == 0) {
      dfs(x / 2);
      power_map[x] = power_map[x / 2] + 1;
    } else {
      dfs((x * 3 + 1) / 2);
      power_map[x] = power_map[(x * 3 + 1) / 2] + 2;
    }
  }

  int getKth(int lo, int hi, int k)
  {
    int len = hi - lo + 1;
    std::vector<int> arr(len);
    for (int i = 0; i < len; ++i) arr[i] = lo + i;
    for (int i = lo; i <= hi; ++i) dfs(i);

    // unstable sort
    std::ranges::sort(arr, {}, [&](int x){
      return std::pair{power_map[x], x};
    });
    return arr[k - 1];
  }
};
// clang-format on
