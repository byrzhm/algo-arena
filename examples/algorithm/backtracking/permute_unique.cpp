#include <bits/stdc++.h>

std::vector<std::vector<int>> unique_permute(std::vector<int> &nums) {
  std::vector<std::vector<int>> res;
  std::function<void(int)> backtracking = [&](int step) {
    if (step == nums.size()) {
      res.push_back(nums);
    } else {
      std::unordered_map<int, bool> vis;
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

int main() {
  std::vector<int> nums{1, 1, 2, 2};
  auto res = unique_permute(nums);
  for (const auto & row : res) {
    for (const auto & num : row) {
      std::cout << num << " ";
    }
    std::cout << "\n";
  }
}