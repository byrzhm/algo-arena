#include <iostream>
#include <vector>
using std::cout;
using std::swap;
using std::vector;

class Solution
{
public:
  void sortColors(vector<int> &nums)
  {
    auto p0 = nums.begin();
    auto p2 = nums.end() - 1;

    for (auto iter = nums.begin(); iter <= p2; ++iter) {
      while (iter <= p2 && *iter == 2) {
        swap(*iter, *p2);
        --p2;
      }
      if (iter >= p0 && *iter == 0) {
        swap(*iter, *p0);
        ++p0;
      }
    }
  }
};

int main()
{
  auto printVec = [](vector<int> &nums) {
    for (auto num : nums) {
      cout << num << ' ';
    }
    cout << '\n';
  };
  {
    vector<int> nums = {1, 2, 0};
    Solution().sortColors(nums);
    printVec(nums);
  }
  {
    vector<int> nums = {2, 1, 2};
    Solution().sortColors(nums);
    printVec(nums);
  }
}