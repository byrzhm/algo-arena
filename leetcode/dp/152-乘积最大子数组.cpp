#include <bits/stdc++.h>

namespace sol1 {

class Solution {
 public:
  int maxProduct(const std::vector<int> &nums) {
    std::vector<int> maxProd(nums.size());
    std::vector<int> minProd(nums.size());
    int max;

    max = maxProd[0] = minProd[0] = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
      maxProd[i] = std::max(std::max(minProd[i - 1] * nums[i], maxProd[i - 1] * nums[i]), nums[i]);
      minProd[i] = std::min(std::min(minProd[i - 1] * nums[i], maxProd[i - 1] * nums[i]), nums[i]);

      if (maxProd[i] > max) {
        max = maxProd[i];
      }
    }

    return max;
  }
};

}  // namespace sol1

namespace sol2 {

class Solution {
 public:
  int maxProduct(const std::vector<int> &nums) {
    int maxProd;
    int minProd;
    int max;

    max = maxProd = minProd = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
      int newMaxProd = std::max(std::max(minProd * nums[i], maxProd * nums[i]), nums[i]);
      int newMinProd = std::min(std::min(minProd * nums[i], maxProd * nums[i]), nums[i]);

      if (newMaxProd > max) {
        max = newMaxProd;
      }

      maxProd = newMaxProd;
      minProd = newMinProd;
    }

    return max;
  }
};

}  // namespace sol2

int main() { std::cout << sol1::Solution().maxProduct(std::vector<int>{-2, 3, -4}) << std::endl; }