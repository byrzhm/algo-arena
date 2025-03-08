#include <algorithm>
#include <endian.h>
#include <numeric>
#include <vector>
namespace ranges = std::ranges;
using std::accumulate;
using std::lower_bound;
using std::vector;



class Solution
{
public:
  long long maximumBeauty(vector<int> &flowers, long long newFlowers, int target, int full, int partial)
  {
    int n = flowers.size();
    ranges::sort(flowers);
    int idx = lower_bound(flowers.begin(), flowers.end(), target) - flowers.begin();
    if (idx == 0) {
      return static_cast<long long>(n) * full;
    }

    long long leftFlowers = newFlowers - (static_cast<long long>(target) * idx - accumulate(flowers.begin(), flowers.begin() + idx, 0LL));
    if (leftFlowers >= 0) {
      return std::max(static_cast<long long>(n) * full, static_cast<long long>(n - 1) * full + static_cast<long long>(target - 1) * partial);
    }

    long long ans    = 0;
    long long preSum = 0;
    int j            = 0;
    for (int i = 1; i <= idx; i++) {
      leftFlowers += target - flowers[i - 1];
      if (leftFlowers < 0) {
        continue;
      }

      while (j < i && static_cast<long long>(flowers[j]) * j <= preSum + leftFlowers) {
        preSum += flowers[j++];
      }

      long long avg         = (preSum + leftFlowers) / j;
      long long totalBeauty = avg * partial + static_cast<long long>(n - i) * full;
      ans                   = std::max(ans, totalBeauty);
    }
    return ans;
  }
};