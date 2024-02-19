#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

class Solution
{
public:
  int maxArea(std::vector<int> &height)
  {
    int n = height.size();
    int l = 0, r = n - 1;
    int max_area = std::numeric_limits<int>::min();

    while (l < r) {
      int lh   = height[l];
      int rh   = height[r];
      int area = std::min(lh, rh) * (r - l);
      max_area = std::max(area, max_area);

      if (lh < rh) {
        ++l;
      } else {
        --r;
      }
    }

    return max_area;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
  std::cout << Solution().maxArea(height) << '\n';

  return 0;
}