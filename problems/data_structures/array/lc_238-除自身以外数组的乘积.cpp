#include <vector>

namespace divide {

class Solution
{
public:
  std::vector<int> productExceptSelf(std::vector<int> &nums)
  {
    int64_t tot_prod = 1;
    for (auto num : nums) {
      tot_prod *= num;
    }
    std::vector<int> ans(nums);
    for (auto &num : ans) {
      num = tot_prod / num;  // divide by zero
    }
    return ans;
  }
};

}  // namespace divide

namespace nodiv {

class Solution
{
public:
  std::vector<int> productExceptSelf(std::vector<int> &nums)
  {
    int n = nums.size();
    std::vector<int> ans(n, 1);
    for (int i = 1; i < n; ++i) {
      ans[i] = ans[i - 1] * nums[i - 1];
    }
    int tmp = 1;
    for (int j = n - 2; j >= 0; --j) {
      tmp *= nums[j + 1];
      ans[j] *= tmp;
    }
    return ans;
  }
};

}  // namespace nodiv
