#include <bits/stdc++.h>

namespace bruteforce {

class Solution {
 public:
  int findMin(std::vector<int> &nums) {
    int min = std::numeric_limits<int>::max();
    for (int num : nums) {
      min = std::min(min, num);
    }
    return min;
  }
};

}  // namespace bruteforce

namespace binary_search {

class Solution {
 public:
  int findMin(std::vector<int> &nums) {
    int left = 0;
    int right = nums.size() - 1;

    // nums.size() == 1 不进入循环

    while (left < right) {               // left < right
      int middle = (left + right) >> 1;  // middle 偏向 left
      if (nums[middle] < nums[right]) {  // middle != right
        right = middle;                  // [left, right] -> [left, middle]
      } else {                           // nums[middle] > nums[right]
        left = middle + 1;               // [left, right] -> [middle + 1, right]
      }
    }
    return nums[left];
  }
};

}  // namespace binary_search

namespace iterator_binary_search {

class Solution {
 public:
  int findMin(std::vector<int> &nums) {
    int len = nums.size();
    auto first = nums.begin();
    while (len > 1) {
      int half = (len - 1) >> 1;  // len - 1 = right - left
      auto middle = first;
      std::advance(middle, half);  // 要让middle偏向first

      if (*middle < *(first + len - 1)) {  // 右侧升序, 最小值在左侧(可能是middle)
        len = half + 1;
      } else {  // 左侧升序, 最小值在右侧
        first = middle;
        ++first;
        len = len - half - 1;
      }
    }
    return *first;
  }
};

}  // namespace iterator_binary_search

int main() {
  std::vector<int> nums = {3, 4, 5, 1, 2};
  std::cout << binary_search::Solution().findMin(nums) << std::endl;
}