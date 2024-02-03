#include <bits/stdc++.h>

class Solution
{
public:
  int singleNumber(std::vector<int> &nums)
  {
    int ans = 0;
    for (int num : nums)
      ans = ans ^ num;
    return ans;
  }
};