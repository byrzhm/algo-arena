#include <algorithm>
#include <vector>
using std::vector;
namespace ranges = std::ranges;

// clang-format off
class Solution {
public:
  long long minimumCost(int m, int n, vector<int> &horizontalCut, vector<int> &verticalCut) {
    ranges::sort(horizontalCut);
    ranges::sort(verticalCut);
    long long h = 1, v = 1;
    long long res = 0;
    while (!horizontalCut.empty() || !verticalCut.empty()) {
      if (verticalCut.empty() || !horizontalCut.empty() && horizontalCut.back() > verticalCut.back()) {
        res += horizontalCut.back() * h;
        horizontalCut.pop_back();
        v++;
      } else {
        res += verticalCut.back() * v;
        verticalCut.pop_back();
        h++;
      }
    }
    return res;
  }
};
// clang-format on