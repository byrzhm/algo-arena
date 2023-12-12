#include <bits/stdc++.h>

std::vector<std::vector<int>> permute(std::vector<int> &nums) {
  std::vector<std::vector<int>> res;
  std::function<void(int)> backtracking = [&](int step) {
    if (step == nums.size()) {
      res.push_back(nums);
    } else {
      for (int i = step; i < nums.size(); ++i) {
        std::swap(nums[step], nums[i]); // choose
        backtracking(step + 1);
        std::swap(nums[step], nums[i]); // unchoose
      }
    }
  };
  backtracking(0);
  return res;
}

int main() {
  std::vector<int> nums{1, 2, 3, 4};
  std::vector<std::vector<int>> permutations = permute(nums);
  for (const auto & permutation : permutations) {
    for (const auto & num : permutation) {
      std::cout << num << " ";
    }
    std::cout << "\n";
  }
}