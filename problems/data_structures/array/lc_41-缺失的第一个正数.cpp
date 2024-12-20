#include <iostream>
#include <utility>
#include <vector>

class Solution
{
public:
  int firstMissingPositive(std::vector<int> &nums)
  {
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      while (nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1]) {
        std::swap(nums[nums[i] - 1], nums[i]);
      }
    }
    for (int i = 0; i < n; ++i) {
      if (nums[i] != i + 1) {
        return i + 1;
      }
    }
    return n + 1;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<int> nums = {3, 4, -1, 1};
  std::cout << Solution().firstMissingPositive(nums) << '\n';

  return 0;
}