#include <bits/stdc++.h>

namespace stl_lower_bound {

class Solution {
 public:
  int searchInsert(std::vector<int> &nums, int target) {
    auto pos = std::lower_bound(nums.begin(), nums.end(), target);
    return pos - nums.begin();
  }
};

}  // namespace stl_lower_bound

namespace my_lower_bound {

class Solution {
 public:
  int searchInsert(std::vector<int> &nums, int target) {
    auto pos = my_lower_bound(nums.begin(), nums.end(), target);
    return pos - nums.begin();
  }

 private:
  std::vector<int>::iterator my_lower_bound(std::vector<int>::iterator first, std::vector<int>::iterator last,
                                            const int &val) {
    auto len = std::distance(first, last);
    while (len > 0) {
      auto half = len >> 1;  // half = (last - first)/2
      auto middle = first;
      std::advance(middle, half);  // middle = first + half
      if (*middle < val) {
        first = middle;
        ++first;
        len = len - half - 1;
      } else {
        len = half;  // last = middle
      }
    }
    return first;
  }
};

}  // namespace my_lower_bound
