#include <functional>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

using std::greater;
using std::min;
using std::numeric_limits;
using std::sort;
using std::string;
using std::unordered_map;
using std::vector;

namespace sort_cnt {

class Solution
{
public:
  int minimumDeletions(const string &word, int k)
  {
    vector<int> cnt(26, 0);
    // 扫描获取每个字母出现的次数
    for (auto c : word)
      ++cnt[c - 'a'];

    // 将次数按从大到小排序
    sort(cnt.begin(), cnt.end(), greater<>());

    // 找到最后一个不为0的数
    int idx = 25;
    while (idx >= 0 && cnt[idx] == 0) {
      --idx;
    }

    int del = INT_MAX;
    for (int end = idx; end >= 0; --end) {
      int curr = 0;
      for (int i = end + 1; i <= idx; ++i) {
        curr += cnt[i];
      }

      if (curr >= del)
        continue;

      // cout << curr << ": ";
      int temp = cnt[0];
      if (temp - cnt[end] > k) {
        temp  = cnt[end] + k;
        curr += cnt[0] - temp;
      }

      for (int i = 1; i < end; ++i) {
        if (cnt[i] <= temp)
          break;
        curr += cnt[i] - temp;
      }
      // cout << curr << endl;
      del = min(del, curr);
    }
    return del;
  }
};

}  // namespace sort_cnt

namespace counter {

class Solution
{
public:
  int minimumDeletions(const string &word, int k)
  {
    int n = word.length();
    unordered_map<char, int> map;
    // 扫描获取每个字母出现的次数
    for (int i = 0; i < n; ++i)
      ++map[word[i]];

    int ans = numeric_limits<int>::max();
    for (int i = 0; i <= n; ++i) {
      int del = 0;
      for (auto &[c, cnt] : map) {
        if (cnt < i)
          del += cnt;
        if (cnt > i + k)
          del += cnt - (i + k);
      }
      ans = min(ans, del);
    }

    return ans;
  }
};

}  // namespace counter