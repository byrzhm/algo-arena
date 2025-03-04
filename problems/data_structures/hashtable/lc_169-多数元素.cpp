#include <algorithm>
#include <unordered_map>
#include <vector>
using std::unordered_map;
using std::vector;
namespace ranges = std::ranges;

namespace hashmap {

class Solution
{
public:
  int majorityElement(vector<int> &nums)
  {
    int major = nums[0];
    unordered_map<int, int> hashMap;
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
  int majorityElement(vector<int> &nums)
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

namespace sort {

class Solution
{
public:
  int majorityElement(vector<int> &nums)
  {
    ranges::sort(nums);
    return nums[nums.size() / 2];
  }
};

}  // namespace sort