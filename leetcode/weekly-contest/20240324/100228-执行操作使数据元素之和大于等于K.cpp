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
        int sum  = elem * (times - i + 1);
        if (sum >= k)
          return true;
      }
      return false;
    };

    int l = 1, r = k - 1;

    while (l < r) {
      int mid = (l + r) >> 1;
      if (checkFn(mid)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return l;
  }
};

}  // namespace binary_search
