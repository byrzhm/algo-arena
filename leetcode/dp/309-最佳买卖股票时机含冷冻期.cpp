#include <vector>
using std::vector;

class Solution
{
public:
  int maxProfit(vector<int> &prices)
  {
    if (prices.empty())
      return 0;

    int f0 = 0;
    int f1 = 0;
    int f2 = -prices[0];

    for (auto p : prices) {
      int new_f1 = std::max(f1, f2 + p);
      int new_f2 = std::max(f2, f0 - p);
      f0         = f1;
      f1         = new_f1;
      f2         = new_f2;
    }

    return f1;
  }
};