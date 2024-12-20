#include <bits/stdc++.h>

namespace hashmap {

class Solution
{
public:
  int majorityElement(std::vector<int> &nums)
  {
    int major = nums[0];
    std::unordered_map<int, int> hashMap;
    for (int num : nums) {
      hashMap[num]++;
    }

    for (auto [num, freq] : hashMap) {
      if (freq > hashMap[major]) {
        major = num;
      }
    }
    return major;
  }
};

}  // namespace hashmap

namespace Boyer_Moore {

class Solution
{
public:
  int majorityElement(std::vector<int> &nums)
  {
    int candidate;
    int count = 0;
    for (int num : nums) {
      if (count == 0) {
        candidate = num;
      }
      count += (num == candidate) ? +1 : -1;
    }
    return candidate;
  }
};

}  // namespace Boyer_Moore