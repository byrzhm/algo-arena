#include <bits/stdc++.h>

class Solution {
 public:
  std::vector<std::vector<int>> subsets(std::vector<int> &nums) {
    std::vector<std::vector<int>> results;
    std::vector<int> subset;
    int n = nums.size();
    std::function<void(int)> backtracking = [&](int step) {
      if (step == n) {
        results.emplace_back(subset);
        return;
      }

      backtracking(step + 1);

      subset.push_back(nums[step]);
      backtracking(step + 1);
      subset.pop_back();
    };
    backtracking(0);
    return results;
  }
};