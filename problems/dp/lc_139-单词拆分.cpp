#include <bits/stdc++.h>

class Solution {
 public:
  bool wordBreak(const std::string &s, std::vector<std::string> &wordDict) {
    std::unordered_set<std::string> wordSet;
    for (auto &word : wordDict) {
      wordSet.insert(word);
    }

    // dp[i] : 字符串 s 的前 i 个字符是否可以分割
    std::vector<bool> dp(s.size() + 1, false);
    dp[0] = true;

    for (int i = 1; i <= s.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        // 如果前 j 个字符可以被分割(s[0..j-1]可以被分割)
        // 那么如果 s[j..i-1] 刚好是字典里面的一个单词, 那么前 i 个字符也可以分割(i > j)
        if (dp[j] && wordSet.count(s.substr(j, i - j)) > 0) {
          dp[i] = true;
          std::cout << i << std::endl;
          break;
        }
      }
    }
    return dp[s.size()];
  }
};

int main() {
  std::vector<std::string> wordDict = {"leet", "code"};
  std::cout << Solution().wordBreak("leetcode", wordDict) << std::endl;
}