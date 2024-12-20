#include <bits/stdc++.h>

class Solution
{
public:
  int returnToBoundaryCount(std::vector<int> &nums)
  {
    int count = 0;
    int dist  = 0;
    for (int num : nums) {
      dist += num;
      if (dist == 0) {
        ++count;
      }
    }
    return count;
  }
};