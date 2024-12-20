#include <algorithm>
#include <limits>
#include <vector>

using std::vector;

class Solution
{
public:
  long long minimumMoves(vector<int> &nums, int k, int maxChanges)
  {
    int c = 0;
    vector<int> pos;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] == 1) {
        pos.emplace_back(i);
        c = std::max(c, 1);
        if (i + 1 < nums.size() && nums[i + 1] == 1) {
          if (i + 2 < nums.size() && nums[i + 2] == 1) {
            c = 3;
          } else {
            c = std::max(c, 2);
          }
        }
      }
    }

    c = std::min(c, k);
    if (maxChanges >= k - c) {
      return std::max(c - 1, 0) + 2 * (k - c);
    }

    int n = pos.size();
    vector<long long> prefix(n + 1);
    for (int i = 1; i <= n; ++i) {
      prefix[i] = prefix[i - 1] + pos[i - 1];
    }

    int size = k - maxChanges;
    long long ans = std::numeric_limits<long long>::max();

    for (int right = size; right <= n; ++right) {
      int left = right - size;
      int mid = left + (size >> 1);
      long long midPos = pos[mid];
      long long s1 = midPos * (mid - left) - (prefix[mid] - prefix[left]);
      long long s2 = (prefix[right] - prefix[mid]) - midPos * (right - mid);
      ans = std::min(ans, s1 + s2);
    }
    return ans + 2 * maxChanges;
  }
};