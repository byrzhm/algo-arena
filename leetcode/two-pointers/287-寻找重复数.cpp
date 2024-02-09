#include <bits/stdc++.h>

namespace hashtable {

class Solution
{
public:
  int findDuplicate(std::vector<int> &nums)
  {
    std::unordered_map<int, int> hashMap;
    for (auto num : nums) {
      ++hashMap[num];
      if (hashMap[num] > 1) {
        return num;
      }
    }

    return {};
  }
};

}  // namespace hashtable

namespace two_pointer {

class Solution
{
public:
  int findDuplicate(std::vector<int> &nums)
  {
    int slow = 0;
    int fast = 0;

    while (true) {
      slow = nums[slow];
      fast = nums[nums[fast]];

      if (slow == fast)
        break;
    }

    fast = 0;

    while (fast != slow) {
      slow = nums[slow];
      fast = nums[fast];
    }

    return fast;
  }
};

}  // namespace two_pointer

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<int> nums = {1, 3, 4, 2, 2};
  std::cout << hashtable::Solution().findDuplicate(nums) << std::endl;

  return 0;
}