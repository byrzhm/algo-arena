#include <iostream>
#include <vector>

using std::vector;

namespace normal {

class NumArray
{
  std::vector<int> nums;

public:
  explicit NumArray(vector<int> &nums)
  {
    this->nums = std::vector<int>(nums);
  }

  void update(int index, int val)
  {
    nums[index] = val;
  }

  int sumRange(int left, int right)
  {
    int sum = 0;
    for (int i = left; i <= right; ++i) {
      sum += nums[i];
    }
    return sum;
  }
};

}  // namespace normal

namespace prefix_sum {

class NumArray
{
  std::vector<int> nums;
  std::vector<int> prefix;

public:
  explicit NumArray(vector<int> &nums)
  {
    this->nums = std::vector<int>(nums);
    prefix     = std::vector<int>(nums);
    for (int i = 1; i < prefix.size(); ++i) {
      prefix[i] = prefix[i - 1] + prefix[i];
    }
  }

  void update(int index, int val)
  {
    int diff    = val - nums[index];
    nums[index] = val;
    for (int i = index; i < prefix.size(); ++i) {
      prefix[i] += diff;
    }
  }

  int sumRange(int left, int right)
  {
    if (left == 0)
      return prefix[right];
    return prefix[right] - prefix[left - 1];
  }
};

}  // namespace prefix_sum

namespace fenwick {

class NumArray
{
  std::vector<int> arr;
  std::vector<int> tree;

public:
  explicit NumArray(vector<int> &nums)
    : arr(std::move(nums))
  {
    int n = arr.size();
    tree.resize(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
      tree[i]  += arr[i - 1];
      int next = i + (i & -i);  // 下一个关键区间的右端点
      if (next <= n)
        tree[next] += tree[i];
    }
  }

  void update(int index, int val)
  {
    int diff = val - arr[index];
    arr[index] = val;
    for (int i = index + 1; i < tree.size(); i += i & -i) {
      tree[i] += diff;
    }
  }

  int sumRange(int left, int right)
  {
    return getsum(right + 1) - getsum(left);
  }

private:
  int lowbit(int i)
  {
    return i & -i;
  }

  int getsum(int i)
  {  // a[1] + a[2] + ... + a[i]
    int sum = 0;
    while (i > 0) {
      sum += tree[i];
      i   -= lowbit(i);
    }
    return sum;
  }
};

}  // namespace fenwick


/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<int> nums {1, 3, 5};
  fenwick::NumArray numArr(nums);
  std::cout << numArr.sumRange(0, 2) << '\n';
  numArr.update(1, 2);
  std::cout << numArr.sumRange(0, 2) << '\n';


  return 0;
}