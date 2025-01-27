#include <vector>
using std::vector;

namespace dp {

class Solution
{
public:
  int jump(std::vector<int> &nums)
  {
    int n = nums.size();
    std::vector<int> jumps(n, std::numeric_limits<int>::max());
    jumps.front() = 0;

    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (nums[j] + j >= i && jumps[i] > jumps[j] + 1) {
          jumps[i] = jumps[j] + 1;
          break;
        }
      }
    }

    return jumps[n - 1];
  }
};

}  // namespace dp

namespace greedy {

class Solution
{
public:
  int jump(std::vector<int> &nums)
  {
    int n      = nums.size();
    int maxPos = 0;
    int end    = 0;
    int step   = 0;
    for (int i = 0; i < n - 1; ++i) {
      if (i <= maxPos) {
        maxPos = std::max(maxPos, i + nums[i]);
        if (i == end) {
          end = maxPos;
          ++step;
        }
      }
    }
    return step;
  }
};

}  // namespace greedy
