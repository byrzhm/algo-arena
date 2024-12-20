#include <bits/stdc++.h>

class Solution
{
public:
  void sortColors(std::vector<int> &nums)
  {
    auto p0 = nums.begin();
    auto p2 = nums.end() - 1;

    for (auto iter = nums.begin(); iter <= p2; ++iter) {
      while (iter <= p2 && *iter == 2) {
        std::swap(*iter, *p2);
        --p2;
      }
      if (iter >= p0 && *iter == 0) {
        std::swap(*iter, *p0);
        ++p0;
      }
    }
  }
};

int main()
{
  auto printVec = [](std::vector<int> &nums) {
    for (auto num : nums) {
      std::cout << num << ' ';
    }
    std::cout << '\n';
  };
  {
    std::vector<int> nums = {1, 2, 0};
    Solution().sortColors(nums);
    printVec(nums);
  }
  {
    std::vector<int> nums = {2, 1, 2};
    Solution().sortColors(nums);
    printVec(nums);
  }
}