#include <bits/stdc++.h>

namespace sol1 {

class Solution {
 public:
  int climbStairs(int n) {
    int p = 0, q = 0, r = 1;
    for (int i = 0; i < n; i++) {
      p = q;
      q = r;
      r = p + q;
    }
    return r;
  }
};

}  // namespace sol1

namespace sol2 {

/**
 * 矩阵快速幂
 */

}  // namespace sol2