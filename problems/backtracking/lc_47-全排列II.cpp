#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

using std::function;
using std::unordered_map;
using std::vector;

namespace sol1 {

// clang-format off
class Solution {
public:
  vector<vector<int>> permuteUnique(vector<int> &nums) {
    vector<vector<int>> res;
    function<void(int)> backtracking = [&](int step) {
      if (step == nums.size()) {
        res.push_back(nums);
      } else {
        unordered_map<int, bool> vis;
        for (int i = step; i < nums.size(); ++i) {
          if (vis.find(nums[i]) != vis.end()) {
            continue;
          }
          vis[nums[i]] = true;
          std::swap(nums[i], nums[step]);
          backtracking(step + 1);
          std::swap(nums[i], nums[step]);
        }
      }
    };
    backtracking(0);
    return res;
  }
};
// clang-format on

}  // namespace sol1

namespace sol2 {

// clang-format off
class Solution {
public:
  vector<vector<int>> permuteUnique(vector<int> &nums) {
    vector<vector<int>> res;
    vector<int> path;
    int n = nums.size();
    vector<int> vis(n);
    std::ranges::sort(nums);
    auto dfs = [&](auto&& dfs, int idx) {
      if (idx == n) {
        res.emplace_back(path);
        return;
      }

      for (int i = 0; i < n; ++i) {
        if (vis[i] || (i > 0 && nums[i] == nums[i - 1] && !vis[i - 1])) {
          // 第二个条件保证 [从左往右第一个未被填过的数字]
          continue;
        }

        path.emplace_back(nums[i]);
        vis[i] = 1;
        dfs(dfs, idx + 1);
        vis[i] = 0;
        path.pop_back();
      }
    };
    dfs(dfs, 0);
    return res;
  }
};
// clang-format on

}  // namespace sol2