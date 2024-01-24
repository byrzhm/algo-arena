#include <bits/stdc++.h>

class Solution {
 public:
  std::string longestPalindrome(const std::string &s) {
    int n = s.size();
    if (n == 1) {
      return s;
    }

    if (n == 2) {
      return (s[0] == s[1]) ? s : s.substr(0, 1);
    }

    int maxLen = 1;
    int begin = 0;

    std::vector<std::vector<bool>> dp(n, std::vector<bool>(n));
    // 长度为一的均为回文串
    for (int i = 0; i < n; ++i) dp[i][i] = true;

    for (int l = 2; l <= n; ++l) {           // 长度
      for (int i = 0; i + l - 1 < n; ++i) {  // 左端点
        int j = i + l - 1;                   // 右端点

        if (l == 2) {
          dp[i][j] = s[i] == s[j];
        } else {
          dp[i][j] = (s[i] == s[j]) && (dp[i + 1][j - 1]);
        }

        if (dp[i][j] && l > maxLen) {
          maxLen = l;
          begin = i;
        }
      }
    }

    return s.substr(begin, maxLen);
  }
};