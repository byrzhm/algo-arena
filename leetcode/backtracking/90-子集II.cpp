#include <bits/stdc++.h>

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