#include <bits/stdc++.h>

class Solution
{
public:
  bool canJump(std::vector<int> &nums)
  {
    auto rightmost = nums.begin();
    for (auto iter = nums.begin(); iter != nums.end(); ++iter) {
      if (iter <= rightmost) {
        rightmost = std::max(iter + *iter, rightmost);
        if (rightmost >= nums.end() - 1) {
          return true;
        }
      }
    }
    return false;
  }
};
