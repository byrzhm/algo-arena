#include <array>
#include <set>
#include <vector>

using std::array;
using std::multiset;
using std::vector;

class Solution
{
public:
  int minimumDistance(vector<vector<int>> &points)
  {
    int n = points.size();
    vector<array<int, 2>> a(n);
    for (int i = 0; i < n; ++i) {
      a[i][0] = points[i][0] + points[i][1];
      a[i][1] = points[i][0] - points[i][1];
    }

    multiset<int> sum, diff;
    for (int i = 0; i < n; ++i) {
      sum.insert(a[i][0]);
      diff.insert(a[i][1]);
    }

    int ret = 1e9;
    for (int k = 0; k < n; ++k) {
      sum.extract(a[k][0]);  // delete kth point
      diff.extract(a[k][1]);
      int cur = std::max(*sum.rbegin() - *sum.begin(), *diff.rbegin() - *diff.begin());
      ret     = std::min(ret, cur);
      sum.insert(a[k][0]);  // restore kth point
      diff.insert(a[k][1]);
    }
    return ret;
  }
};