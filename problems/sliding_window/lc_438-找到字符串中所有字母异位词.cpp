#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

class Solution
{
public:
  std::vector<int> findAnagrams(const std::string &s, const std::string &p)
  {
    std::vector<int> ans;
    int sLen = s.length();
    int pLen = p.length();

    if (sLen < pLen) {
      return {};
    }

    std::unique_ptr<int[]> count = std::make_unique<int[]>(26);
    std::memset(count.get(), 0, 26 * sizeof(int));

    for (int i = 0; i < pLen; ++i) {
      ++count[s[i] - 'a'];
      --count[p[i] - 'a'];
    }

    int diff = 0;
    for (int i = 0; i < 26; ++i) {
      if (count[i] != 0)
        ++diff;
    }

    if (diff == 0) {
      ans.emplace_back(0);
    }

    for (int i = 0; i < sLen - pLen; ++i) {
      int j = i + pLen;
      // change diff before: 👇
      // ++count[s[j] - 'a'];
      // --count[s[i] - 'a'];

      if (count[s[i] - 'a'] == 1) {
        --diff;
      } else if (count[s[i] - 'a'] == 0) {
        ++diff;
      }
      // else diff doesn't change

      --count[s[i] - 'a'];

      if (count[s[j] - 'a'] == -1) {
        --diff;
      } else if (count[s[j] - 'a'] == 0) {
        ++diff;
      }
      // else diff doesn't change

      ++count[s[j] - 'a'];

      if (diff == 0) {
        ans.emplace_back(i + 1);
      }
    }
    return ans;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  for (auto x : Solution().findAnagrams("cbaebabacd", "abc")) {
    std::cout << x << '\n';
  }

  std::cout << '\n';

  for (auto x : Solution().findAnagrams("bpaa", "aa")) {
    std::cout << x << '\n';
  }

  return 0;
}