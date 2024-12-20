#include <bits/stdc++.h>

namespace dp {

class Solution
{
public:
  int trap(std::vector<int> &height)
  {
    int ans = 0;
    int n   = height.size();
    std::vector<int> leftMax(n);
    std::vector<int> rightMax(n);
    leftMax[0] = rightMax[n - 1] = 0;
    for (int i = 1, j = n - 2; i < n; ++i, --j) {
      leftMax[i]  = std::max(height[i - 1], leftMax[i - 1]);
      rightMax[j] = std::max(height[j + 1], rightMax[j + 1]);
    }

    for (int i = 0; i < n; ++i) {
      int amount = std::min(leftMax[i], rightMax[i]) - height[i];
      if (amount > 0)
        ans += amount;
    }
    return ans;
  }
};

}  // namespace dp

namespace mono_stack {

// 按行算
class Solution
{
public:
  int trap(std::vector<int> &height)
  {
    int n = height.size();
    std::stack<int> monoStack;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      while (!monoStack.empty() && height[monoStack.top()] < height[i]) {
        int top = monoStack.top();
        monoStack.pop();
        if (monoStack.empty())
          break;
        int left        = monoStack.top();
        int currWidth   = i - left - 1;
        int currHeight  = std::min(height[left], height[i]) - height[top];
        ans            += currWidth * currHeight;
      }
      monoStack.push(i);
    }
    return ans;
  }
};

}  // namespace mono_stack

namespace two_pointer {

class Solution
{
public:
  int trap(std::vector<int> &height)
  {
    int n = height.size();
    int l = 0, r = n - 1;
    int lMax = 0, rMax = 0;
    int ans = 0;
    while (l < r)
    {
      lMax    = std::max(height[l], lMax);
      rMax    = std::max(height[r], rMax);
      int min = std::min(lMax, rMax);

      if (lMax <= rMax) {
        ans += lMax - height[l];
        ++l;
      } else {
        ans += rMax - height[r];
        --r;
      }
    }
    return ans;
  }
};

}  // namespace two_pointer

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  return 0;
}