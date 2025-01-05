#include <algorithm>
#include <unordered_map>
#include <utility>
using std::max;
using std::pair;
using std::unordered_map;


class MyCalendarTwo
{
public:
  MyCalendarTwo() = default;

  void update(int start, int end, int val, int l, int r, int idx)
  {
    if (r < start || end < l) {
      return;
    }
    if (start <= l && r <= end) {
      tree[idx] += val;
      lazy[idx] += val;
    } else {
      int mid = (l + r) >> 1;
      update(start, end, val, l, mid, 2 * idx);
      update(start, end, val, mid + 1, r, 2 * idx + 1);
      tree[idx] = lazy[idx] + max(tree[2 * idx], tree[2 * idx + 1]);
    }
  }

  bool book(int start, int end)
  {
    update(start, end - 1, 1, 0, 1e9, 1);
    if (tree[1] > 2) {
      update(start, end - 1, -1, 0, 1e9, 1);
      return false;
    }
    return true;
  }

private:
  unordered_map<int, int> tree;
  unordered_map<int, int> lazy;
};