#include <algorithm>
#include <utility>
#include <vector>

namespace bruteforce {

class Solution
{
public:
  long long largestSquareArea(std::vector<std::vector<int>> &bottomLeft, std::vector<std::vector<int>> &topRight)
  {
    long long ans = 0;
    int n         = bottomLeft.size();
    for (int i = 0; i < n - 1; ++i) {
      for (int j = i + 1; j < n; ++j) {
        std::pair<int, int> bl, tr;
        bl.first  = std::max(bottomLeft[i][0], bottomLeft[j][0]);
        bl.second = std::max(bottomLeft[i][1], bottomLeft[j][1]);
        tr.first  = std::min(topRight[i][0], topRight[j][0]);
        tr.second = std::min(topRight[i][1], topRight[j][1]);

        if (bl.first < tr.first && bl.second < tr.second) {
          long long side = std::min(tr.first - bl.first, tr.second - bl.second);
          ans            = std::max(ans, side * side);
        }
      }
    }
    return ans;
  }
};

}  // namespace bruteforce
