#include <bits/stdc++.h>

class Solution {
 public:
  std::vector<int> searchRange(std::vector<int> &nums, int target) {
    auto begin = std::lower_bound(nums.begin(), nums.end(), target);
    if (begin == nums.end() || *begin != target) return {-1, -1};

    auto end = std::upper_bound(nums.begin(), nums.end(), target);
    return {static_cast<int>(begin - nums.begin()), static_cast<int>(end - 1 - nums.begin())};
  }
};

int main() {
  std::vector<int> nums = {5, 7, 7, 8, 8, 10};
  int target = 8;
  auto ans = Solution().searchRange(nums, target);
  std::cout << "{" << ans[0] << ", " << ans[1] << "}" << std::endl;
}