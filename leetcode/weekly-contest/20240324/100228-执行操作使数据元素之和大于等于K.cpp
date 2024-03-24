#include <cmath>

namespace math {

class Solution
{
public:
  int minOperations(int k)
  {
    return ceil(2 * sqrt(k) - 2);
  }
};

}  // namespace math

namespace binary_search {

class Solution
{
public:
  int minOperations(int k)
  {
    if (k == 1)
      return 0;

    auto checkFn = [&](int times) {
      for (int i = 0; i <= times; ++i) {
        int elem = 1 + i;
        int sum  = elem;
        for (int j = times - i; j > 0; --j) {
          sum += elem;
        }
        if (sum >= k)
          return true;
      }
      return false;
    };

    int l = 1, r = k - 1;

    while (l < r) {
      int mid = (l + r) >> 1;
      // printf("l=%d, r=%d, mid=%d\n", l, r, mid);
      if (checkFn(mid)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    // printf("l=%d, r=%d\n", l, r);
    return l;
  }
};

}  // namespace binary_search
