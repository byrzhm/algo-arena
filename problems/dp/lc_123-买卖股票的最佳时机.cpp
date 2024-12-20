#include <array>
#include <climits>
#include <vector>

using std::array;
using std::vector;

class Solution
{
public:
  int maxProfit(vector<int> &prices)
  {
    int k = 2;
    vector<array<int, 2>> f(k + 2, {INT_MIN, INT_MIN});
    for (int j = 1; j < k + 2; ++j)
      f[j][0] = 0;
    for (int p : prices) {
      for (int j = k + 1; j > 0; --j) {
        f[j][1] = std::max(f[j][1], f[j][0] - p);
        f[j][0] = std::max(f[j][0], f[j - 1][1] + p);
      }
    }

    return f[k + 1][0];
  }
};