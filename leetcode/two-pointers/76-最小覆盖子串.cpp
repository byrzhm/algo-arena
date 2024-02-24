#include <iostream>
#include <limits>
#include <unordered_map>


namespace first {

class Solution
{
public:
  std::string minWindow(const std::string &s, const std::string &t)
  {
    if (t.empty())
      return {};

    std::unordered_map<char, int> need;
    for (auto c : t) {
      ++need[c];
    }

    int needSz  = need.size();
    int matchSz = 0;
    std::unordered_map<char, int> have;

    constexpr auto INF = std::numeric_limits<int>::max();
    int minLen         = INF;
    int minL           = 0;
    int l              = 0;
    int r              = 0;

    while (true) {
      // 无法继续扩张
      if (matchSz != needSz && r >= s.length()) {
        break;
      }

      while (matchSz != needSz && r < s.length()) {
        char c = s[r];
        if (need.count(c) > 0) {
          ++have[c];
          if (have[c] == need[c]) {
            ++matchSz;
          }
        }
        ++r;
      }

      while (matchSz == needSz && l < r) {
        if (need.count(s[l]) > 0) {
          if (have[s[l]] == need[s[l]]) {
            --matchSz;
            if (r - l < minLen) {
              minLen = r - l;
              minL   = l;
            }
          }
          --have[s[l]];
        }
        ++l;
      }
    }

    if (minLen == INF) {
      return {};
    }

    return s.substr(minL, minLen);
  }
};

}  // namespace first

namespace second {

class Solution
{
public:
  std::string minWindow(const std::string &s, const std::string &t)
  {
    if (t.empty())
      return {};

    std::unordered_map<char, int> need;
    for (auto c : t) {
      ++need[c];
    }

    int needSz  = need.size();
    int matchSz = 0;
    std::unordered_map<char, int> have;

    constexpr auto INF = std::numeric_limits<int>::max();
    int minLen         = INF;
    int minL           = 0;
    int l              = 0;
    int n              = s.length();

    for (int r = 0; r < n; ++r) {
      char c = s[r];
      if (need.count(c) > 0) {
        ++have[c];
        if (have[c] == need[c]) {
          ++matchSz;
        }
      }

      while (matchSz == needSz) {
        char c = s[l];
        if (need.count(c) > 0) {
          if (have[c] == need[c]) {
            --matchSz;
            if (r - l + 1 < minLen) {
              minLen = r - l + 1;
              minL   = l;
            }
          }
          --have[c];
        }
        ++l;
      }
    }

    if (minLen == INF) {
      return {};
    }

    return s.substr(minL, minLen);
  }
};

}  // namespace second

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout << first::Solution().minWindow("a", "aa") << '\n';
  std::cout << first::Solution().minWindow("ADOBECODEBANC", "ABC") << '\n';
  std::cout << first::Solution().minWindow("bdab", "ab") << '\n';
  std::cout << second::Solution().minWindow("a", "aa") << '\n';
  std::cout << second::Solution().minWindow("ADOBECODEBANC", "ABC") << '\n';
  std::cout << second::Solution().minWindow("bdab", "ab") << '\n';

  return 0;
}