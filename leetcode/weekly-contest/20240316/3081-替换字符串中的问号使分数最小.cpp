#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution
{
public:
  std::string minimizeStringValue(std::string s)
  {
    std::unordered_map<char, int> cnt;
    for (char c : s) {
      ++cnt[c];
    }

    auto cmp = [](const std::pair<int, int> &lhs, const std::pair<int, int> &rhs) {
      if (lhs.first == rhs.first)
        return lhs.second > rhs.second;
      return lhs.first > rhs.first;
    };

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> heap(cmp);

    for (char c = 'a'; c <= 'z'; ++c) {
      heap.emplace(cnt[c], c);
    }

    int qcnt = cnt['?'];
    std::vector<char> chars;
    while (qcnt-- > 0) {
      auto [freq, c] = heap.top();
      chars.emplace_back(c);
      heap.pop();
      heap.emplace(freq + 1, c);
    }

    std::sort(chars.begin(), chars.end());
    int idx = 0;
    for (auto &c : s) {
      if (c == '?') {
        c = chars[idx++];
      }
    }

    return s;
  }
};

int main()
{
  std::cout << Solution().minimizeStringValue("???") << '\n';
  std::cout << Solution().minimizeStringValue("abcdef??") << '\n';
}