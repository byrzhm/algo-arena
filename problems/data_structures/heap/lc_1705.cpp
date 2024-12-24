#include <functional>
#include <map>
#include <queue>
#include <utility>
#include <vector>
using std::greater;
using std::map;
using std::pair;
using std::priority_queue;
using std::vector;


// clang-format off

/**
 * std::priority_queue
 *     https://en.cppreference.com/w/cpp/container/priority_queue
 */
class Solution {
public:
  int eatenApples(vector<int> &apples, vector<int> &days) {
    int ans = 0;
    int n = apples.size();
    int i = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>>
            minq;
    while (i < n || !minq.empty()) {
      while (!minq.empty() && minq.top().first <= i) minq.pop();
      if (i < n && apples[i] > 0) minq.emplace(i + days[i], apples[i]);
      if (!minq.empty()) {
        ++ans;
        auto [ddl, num] = minq.top(); minq.pop();
        --num;
        if (num > 0) minq.emplace(ddl, num);
      }
      ++i;
    }
    return ans;
  }
};
// clang-format on