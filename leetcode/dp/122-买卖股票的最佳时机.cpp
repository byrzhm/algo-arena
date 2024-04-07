#include <limits>
#include <vector>
using std::vector;

class Solution
{
public:
  int maxProfit(vector<int> &prices)
  {
    int f0 = 0, f1 = std::numeric_limits<int>::min();
    for (auto price : prices) {
      int new_f0 = std::max(f0, f1 + price);
      int new_f1 = std::max(f1, f0 - price);
      f0 = new_f0;
      f1 = new_f1;
    }
    return f0;
  }
};