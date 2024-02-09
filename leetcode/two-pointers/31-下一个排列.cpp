#include <bits/stdc++.h>

namespace stl {

class Solution
{
public:
  void nextPermutation(std::vector<int> &nums)
  {
    std::next_permutation(nums.begin(), nums.end());
  }
};

}  // namespace stl

namespace longest_decreasing_sequence {

class Solution
{
public:
  void nextPermutation(std::vector<int> &nums)
  {
    int n = nums.size();
    int i = n - 2;
    while (i >= 0 && nums[i] >= nums[i + 1]) {
      --i;
    }
    if (i >= 0) {
      int j = n - 1;
      while (nums[j] <= nums[i]) {
        --j;
      }
      std::swap(nums[i], nums[j]);
    }
    std::reverse(nums.begin() + i + 1, nums.end());
  }
};

}  // namespace longest_decreasing_sequence

namespace iterator {

class Solution
{
public:
  void nextPermutation(std::vector<int> &nums)
  {
    if (nums.empty())
      return;
    if (nums.size() == 1)
      return;

    auto i = nums.end();
    --i;

    while (true) {
      auto ii = i;
      --i;

      if (*i < *ii) {  // 找到了到尾部最长递减序列的边界
        auto j = nums.end();
        --j;
        // 寻找递减序列中第一个比 *i 大的
        while (*i >= *j) {
          --j;
        }
        std::iter_swap(i, j);          // 交换i, j指向的数, 后面依然是递减序列
        std::reverse(ii, nums.end());  // 逆转后面的递减序列
        return;
      }

      if (i == nums.begin()) {
        std::reverse(nums.begin(), nums.end());
        return;
      }
    }
  }
};

}  // namespace iterator

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<int> nums{2, 3, 1};
  stl::Solution().nextPermutation(nums);
  for (auto num : nums) {
    std::cout << num << ' ';
  }
  std::cout << std::endl;
  return 0;
}