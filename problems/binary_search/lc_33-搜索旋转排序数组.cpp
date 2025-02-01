#include <iostream>
#include <vector>


namespace bruteforce {

// clang-format off
class Solution {
 public:
  int search(std::vector<int> &nums, int target) {
    for (int i = 0; i < nums.size(); ++i) {
      if (target == nums[i]) {
        return i;
      }
    }
    return -1;
  }
};
// clang-format on

}  // namespace bruteforce

namespace smart_binary_search {

// clang-format off
class Solution {
 public:
  int search(std::vector<int> &nums, int target) {
    auto first = nums.begin();
    int len = nums.size();

    while (len > 0) {
      int half = len >> 1;
      auto middle = first;
      std::advance(middle, half);
      std::vector<int>::iterator iter;
      if (*middle == target) {
        return middle - nums.begin();
      }

      if (*first < *middle) {  // 左侧有序
        iter = std::lower_bound(first, middle, target);
        if (iter != nums.end() && *iter == target) return iter - nums.begin();

        // 可能在无序的一边
        first = middle;
        ++first;
        len = len - half - 1;
      } else {  // 右侧有序
        iter = std::lower_bound(middle + 1, first + len, target);
        if (iter != nums.end() && *iter == target) return iter - nums.begin();

        // 可能在无序的一边
        len = half;
      }
    }
    return -1;
  }
};

}  // namespace smart_binary_search

namespace smarter_binary_search {

class Solution {
 public:
  int search(std::vector<int> &nums, int target) {
    auto first = nums.begin();
    int len = nums.size();

    while (len > 0) {
      int half = len >> 1;
      auto middle = first;
      std::advance(middle, half);
      if (*middle == target) {
        return middle - nums.begin();
      }

      if (*first < *middle) {  // 左侧升序
        if (*first <= target && target < *middle) {
          len = half;
        } else {
          first = middle;
          ++first;
          len = len - half - 1;
        }
      } else {  // 右侧升序
        if (*middle < target && target <= *(first + len - 1)) {
          first = middle;
          ++first;
          len = len - half - 1;
        } else {
          len = half;
        }
      }
    }
    return -1;
  }
};
// clang-format on

}  // namespace smarter_binary_search

int main()
{
  std::vector<int> nums = {5, 1, 3};
  int target            = 3;
  std::cout << smarter_binary_search::Solution().search(nums, target) << '\n';
}