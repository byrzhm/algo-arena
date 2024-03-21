#include <numeric>
#include <queue>
#include <vector>

using std::vector;
using std::accumulate;
using std::pair;
using std::greater;
using std::priority_queue;

class Solution
{
public:
  vector<long long> unmarkedSumArray(vector<int> &nums, vector<vector<int>> &queries)
  {
    int n = nums.size();
    int m = queries.size();
    vector<long long> ans;
    long long sum = accumulate(nums.begin(), nums.end(), 0LL);
    vector<bool> marked(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    for (int i = 0; i < n; ++i) {
      pq.emplace(nums[i], i);
    }

    ans.reserve(m);
    for (auto &query : queries) {
      int index = query[0];
      int k     = query[1];

      if (!marked[index]) {
        marked[index]  = true;
        sum           -= nums[index];
      }

      while (k > 0 && !pq.empty()) {
        auto [num, idx] = pq.top();
        pq.pop();
        if (!marked[idx]) {
          marked[idx]  = true;
          sum         -= nums[idx];
          --k;
        }
      }
      ans.emplace_back(sum);
    }
    return ans;
  }
};