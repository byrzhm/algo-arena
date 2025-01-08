#include <algorithm>
#include <vector>

using std::vector;

namespace sol1 {

class Solution
{
public:
  int maxProduct(const vector<int> &nums)
  {
    vector<int> maxProd(nums.size());
    vector<int> minProd(nums.size());
    int max;

    max = maxProd[0] = minProd[0] = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
      maxProd[i] = std::max({minProd[i - 1] * nums[i], maxProd[i - 1] * nums[i], nums[i]});
      minProd[i] = std::min({minProd[i - 1] * nums[i], maxProd[i - 1] * nums[i], nums[i]});

      max = std::max(maxProd[i], max);
    }

    return max;
  }
};

}  // namespace sol1

namespace sol2 {

class Solution
{
public:
  int maxProduct(const vector<int> &nums)
  {
    int maxProd;
    int minProd;
    int max;

    max = maxProd = minProd = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
      int newMaxProd = std::max({minProd * nums[i], maxProd * nums[i], nums[i]});
      int newMinProd = std::min({minProd * nums[i], maxProd * nums[i], nums[i]});

      max = std::max(newMaxProd, max);

      maxProd = newMaxProd;
      minProd = newMinProd;
    }

    return max;
  }
};

}  // namespace sol2