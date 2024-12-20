#include <bits/stdc++.h>

namespace stl_nth_element {

class Solution
{
public:
  int findKthLargest(std::vector<int> &nums, int k)
  {
    auto kth = nums.end();
    std::advance(kth, -k);
    std::nth_element(nums.begin(), kth, nums.end());
    return *kth;
  }
};

}  // namespace stl_nth_element

namespace heap {

class Solution
{
public:
  int findKthLargest(std::vector<int> &nums, int k)
  {
    // std::priority_queue<int> pq(nums.begin(), nums.end());
    // while (--k != 0) {
    //   pq.pop();
    // }
    // return pq.top();

    // auto printVec = [&nums]() {
    //   for (int num : nums) {
    //     std::cout << num << ' ';
    //   }
    //   std::cout << '\n';
    // };

    std::make_heap(nums.begin(), nums.end());  // 建立最大堆, 堆顶在 nums[0]
    // printVec();
    while (--k != 0) {
      std::pop_heap(nums.begin(), nums.end());  // 将原来最大的元素放在堆低
      // printVec();
      nums.pop_back();  // 必须 pop 防止出错
    }
    return nums.front();
  }
};

}  // namespace heap