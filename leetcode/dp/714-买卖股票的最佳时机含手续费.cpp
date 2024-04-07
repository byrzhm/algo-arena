#include <climits>
#include <cstdint>
#include <vector>
using std::vector;

class Solution
{
public:
  int maxProfit(vector<int> &prices, int fee)
  {
    int64_t f0 = 0, f1 = INT_MIN;
    for (int p : prices) {
      int temp = std::max(f0, f1 + p - fee);
      f1 = std::max(f1, f0 - p);
      f0 = temp;
    }
    return f0;
  }
};