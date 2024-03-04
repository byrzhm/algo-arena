#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

namespace map {

class Solution
{
public:
  std::vector<int> resultArray(std::vector<int> &nums)
  {
    a1.push_back(nums[0]);
    a2.push_back(nums[1]);

    ++s1[nums[0]];
    ++s2[nums[1]];

    for (int i = 2; i < nums.size(); ++i) {
      int cnt1 = greaterCount1(nums[i]);
      int cnt2 = greaterCount2(nums[i]);

      if (cnt1 != cnt2) {
        if (cnt1 > cnt2) {
          a1.push_back(nums[i]);
          ++s1[nums[i]];
        } else {
          a2.push_back(nums[i]);
          ++s2[nums[i]];
        }
      } else {
        if (a1.size() > a2.size()) {
          a2.push_back(nums[i]);
          ++s2[nums[i]];
        } else {
          a1.push_back(nums[i]);
          ++s1[nums[i]];
        }
      }
    }

    std::vector<int> res;
    res.swap(a1);
    for (auto i : a2)
      res.emplace_back(i);

    return res;
  }

  int greaterCount1(int val)
  {
    auto it = s1.upper_bound(val);
    if (it == s1.begin())
      return a1.size();

    int count = 0;
    for (; it != s1.end(); ++it) {
      count += it->second;
    }
    return count;
  }

  int greaterCount2(int val)
  {
    auto it = s2.upper_bound(val);
    if (it == s2.begin())
      return a2.size();

    int count = 0;
    for (; it != s2.end(); ++it) {
      count += it->second;
    }
    return count;
  }

  std::map<int, int> s1;
  std::map<int, int> s2;
  std::vector<int> a1;
  std::vector<int> a2;
};

}  // namespace map

namespace fenwick {

class BIT
{
public:
  explicit BIT(int size)
  {
    arr.resize(size + 1, 0);
    tree.resize(size + 1, 0);
  }

  explicit BIT(std::vector<int> &nums)
  {
    int n = nums.size();
    arr.resize(n + 1, 0);
    tree.resize(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
      arr[i] = nums[i - 1];
    }

    for (int i = 1; i <= n; ++i) {
      tree[i]  += arr[i];
      int next  = i + lowbit(i);
      if (next <= n)
        tree[next] += tree[i];
    }
  }

  void update(int idx, int val)
  {
    int diff = val - arr[idx];
    arr[idx] = val;
    for (int i = idx; i < tree.size(); i += lowbit(i)) {
      tree[i] += diff;
    }
  }

  void increase(int idx, int diff)
  {
    arr[idx] += diff;
    for (int i = idx; i < tree.size(); i += lowbit(i)) {
      tree[i] += diff;
    }
  }

  int getsum(int i)
  {
    int sum = 0;
    while (i > 0) {
      sum += tree[i];
      i   -= lowbit(i);
    }
    return sum;
  }

private:
  constexpr int lowbit(int i)
  {
    return i & -i;
  }

  std::vector<int> arr;
  std::vector<int> tree;
};

class Solution
{
public:
  std::vector<int> resultArray(std::vector<int> &nums)
  {
    sorted = std::vector<int>(nums);
    std::sort(sorted.begin(), sorted.end());
    auto last = std::unique(sorted.begin(), sorted.end());
    sorted.erase(last, sorted.end());

    int size = sorted.size();
    BIT bit1(size);
    BIT bit2(size);

    std::vector<int> a1;
    std::vector<int> a2;

    a1.reserve(nums.size());

    a1.emplace_back(nums[0]);
    a2.emplace_back(nums[1]);

    bit1.increase(indexOf(nums[0]), 1);
    bit2.increase(indexOf(nums[1]), 1);

    for (int i = 2; i < nums.size(); ++i) {
      int idx = indexOf(nums[i]);
      int cnt1 = bit1.getsum(size) - bit1.getsum(idx);
      int cnt2 = bit2.getsum(size) - bit2.getsum(idx);

      if (cnt1 > cnt2 || (cnt1 == cnt2 && a1.size() <= a2.size())) {
        a1.emplace_back(nums[i]);
        bit1.increase(idx, 1);
      } else {
        a2.emplace_back(nums[i]);
        bit2.increase(idx, 1);
      }
    }

    a1.insert(a1.end(), a2.begin(), a2.end());

    return a1;
  }

private:
  int indexOf(int target)
  {
    auto pos = std::lower_bound(sorted.begin(), sorted.end(), target);
    return pos - sorted.begin() + 1;
  }

  std::vector<int> sorted;
};

}  // namespace fenwick


int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<int> nums{2, 38, 2};
  for (auto num : fenwick::Solution().resultArray(nums)) {
    std::cout << num << " ";
  }
  std::cout << '\n';

  return 0;
}