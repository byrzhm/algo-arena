/**
 *  https://www.bilibili.com/video/BV1ho4y1W7QK/?vd_source=571900c3ae9bbfdc988accacb2feb8be
 */
#include <vector>

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