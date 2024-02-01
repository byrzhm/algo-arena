#include <bits/stdc++.h>

class Solution
{
public:
  int maxProfit(std::vector<int> &prices)
  {
    int maxProfit = 0;
    int currMin   = std::numeric_limits<int>::max();
    for (int price : prices) {
      if (price - currMin > maxProfit) {
        maxProfit = price - currMin;
      }
      currMin = std::min(currMin, price);
    }

    return maxProfit;
  }
};