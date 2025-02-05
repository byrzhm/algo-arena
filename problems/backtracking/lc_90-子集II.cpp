#include <algorithm>
#include <functional>
#include <ranges> // IWYU pragma: keep
#include <unordered_set>
#include <vector>

namespace hash {

// clang-format off
class Solution {
 public:
  std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &nums) {
    std::vector<std::vector<int>> subsets;
    std::vector<int> subset;

    auto hasher = [](const std::vector<int> &vec) {
      size_t key = 0;
      for (auto &v : vec) {
        key = key * 21 + (v + 10);
      }
      return key;
    };

    std::unordered_set<std::vector<int>, decltype(hasher)> vec_set(0, hasher);
    std::sort(nums.begin(), nums.end());

    std::function<void(int)> backtracking = [&](int step) {
      if (step == nums.size()) {
        if (vec_set.find(subset) == vec_set.end()) {
          subsets.emplace_back(subset);
          vec_set.emplace(subset);
        }
        return;
      }

      // x[step] = 0
      backtracking(step + 1);

      // x[step] = 1
      subset.push_back(nums[step]);
      backtracking(step + 1);
      subset.pop_back();
    };

    backtracking(0);
    return subsets;
  }
};
// clang-format on

}  // namespace hash


namespace smart {

using std::vector;
namespace ranges = std::ranges;

// clang-format off
class Solution {
  vector<vector<int>> ans;
  vector<int> path;
  int n;
public:
  vector<vector<int>> subsetsWithDup(vector<int> &nums) {
    n = nums.size();
    ranges::sort(nums);
    dfs(0, nums);
    return ans;
  }

  void dfs(int i, vector<int> &nums) {
    if (i == n) {
      ans.push_back(path);
      return;
    }

    int x = nums[i];
    int j = i + 1;
    while (j < n && nums[j] == x) ++j;
    dfs(j, nums);

    path.push_back(x);
    dfs(i + 1, nums);
    path.pop_back();
  }
};
// clang-format on

}  // namespace smart

namespace lambda {

using std::vector;
namespace ranges = std::ranges;

// clang-format off
class Solution {
public:
  vector<vector<int>> subsetsWithDup(vector<int> &nums) {
    vector<vector<int>> ans;
    vector<int> path;
    int n = nums.size();
    ranges::sort(nums);
    auto dfs = [&](auto&& dfs, int i) {
      if (i == n) {
        ans.push_back(path);
        return;
      }

      int x = nums[i];
      int j = i + 1;
      while (j < n && nums[j] == x) ++j;
      dfs(dfs, j);

      path.push_back(x);
      dfs(dfs, i + 1);
      path.pop_back();
    };
    dfs(dfs, 0);
    return ans;
  }
};
// clang-format on

}  // namespace lambda