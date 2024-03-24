#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>
using std::pair;
using std::priority_queue;
using std::unordered_map;
using std::vector;

class Solution
{
public:
  vector<long long> mostFrequentIDs(vector<int> &nums, vector<int> &freq)
  {
    int n = nums.size();
    priority_queue<pair<long long, int>> pq;  // {cnt, num}
    unordered_map<int, long long> count;      // num -> cnt
    vector<long long> ans(n);

    for (int i = 0; i < n; ++i) {
      count[nums[i]] += freq[i];
      pq.emplace(count[nums[i]], nums[i]);

      while (true) {
        auto [cnt, num] = pq.top();
        if (cnt != count[num]) {
          pq.pop();
        } else {
          ans[i] = cnt;
          break;
        }
      }
    }
    return ans;
  }
};