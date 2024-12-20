#include <deque>
#include <iostream>
#include <vector>

class Solution
{
public:
  std::vector<int> maxSlidingWindow(const std::vector<int> &nums, int k)
  {
    std::vector<int> ans;
    std::deque<int> monoQ;
    for (int i = 0; i < nums.size(); ++i) {
      while (!monoQ.empty() && nums[i] > nums[monoQ.back()]) {
        monoQ.pop_back();
      }
      monoQ.push_back(i);
      while (monoQ.front() <= i - k) {
        monoQ.pop_front();
      }

      if (i >= k - 1) {
        ans.push_back(nums[monoQ.front()]);
      }
    }
    return ans;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  for (auto it : Solution().maxSlidingWindow({1, 3, -1, -3, 5, 3, 6, 7}, 3)) {
    std::cout << ' ' << it;
  }
  std::cout << '\n';

  return 0;
}