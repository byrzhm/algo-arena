#include <algorithm>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace slow {

class Solution
{
public:
  int subarraySum(const std::vector<int> &nums, int k)
  {
    int n = nums.size();
    std::vector<int64_t> prefix(n);
    std::unordered_map<int64_t, std::vector<int>> hashMap;

    int64_t sum = 0;
    for (int i = 0; i < n; ++i) {
      sum += nums[i];
      hashMap[sum].emplace_back(i);
      prefix[i] = sum;
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
      if (prefix[i] == k)
        ++ans;
      if (hashMap.count(k + prefix[i]) > 0) {
        auto &indices  = hashMap[k + prefix[i]];
        auto pos       = std::upper_bound(indices.begin(), indices.end(), i);
        ans           += indices.end() - pos;
      }
    }

    return ans;
  }
};

}  // namespace slow

namespace fast {

class Solution
{
public:
  int subarraySum(const std::vector<int> &nums, int k)
  {
    int n = nums.size();
    int sum = 0;
    int ans = 0;
    std::unordered_map<int, int> map;
    map[0] = 1;
    for (int i = 0; i < n; ++i) {
      sum += nums[i];
      if (map.count(sum - k) > 0) {
        ans += map[sum - k];
      }
      ++map[sum];
    }
    return ans;
  }
};

}  // namespace fast

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout << slow::Solution().subarraySum({1, 2, 3}, 3) << '\n';
  std::cout << fast::Solution().subarraySum({1, 2, 3}, 3) << '\n';

  return 0;
}