#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>

namespace hashtable {

class Solution
{
public:
  int lengthOfLongestSubstring(const std::string &s)
  {
    std::unordered_set<char> set;
    int n = s.length();
    int i = 0, j = 0;
    int maxLen = 0;
    while (j < n) {
      while (set.contains(s[j])) {
        set.erase(s[i++]);
      }
      set.insert(s[j]);
      ++j;
      maxLen = std::max(maxLen, j - i);
    }
    return maxLen;
  }
};

}  // namespace hashtable

namespace find {

class Solution
{
public:
  int lengthOfLongestSubstring(const std::string &s)
  {
    int n = s.length();
    int i = 0, j = 0;
    int maxLen = 0;
    while (j < n) {
      int pos = s.find(s[j], i);
      if (pos == j) {  // no repeat between [i..j-1]
        ++j;
        maxLen = std::max(j - i, maxLen);
      } else {
        ++i;
      }
    }
    return maxLen;
  }
};

}  // namespace find

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout << hashtable::Solution().lengthOfLongestSubstring("xxxxx") << '\n';
  std::cout << hashtable::Solution().lengthOfLongestSubstring("xyzxyzzz") << '\n';
  std::cout << hashtable::Solution().lengthOfLongestSubstring("") << '\n';


  std::cout << find::Solution().lengthOfLongestSubstring("xxxxx") << '\n';
  std::cout << find::Solution().lengthOfLongestSubstring("xyzxyzzz") << '\n';
  std::cout << find::Solution().lengthOfLongestSubstring("") << '\n';

  return 0;
}