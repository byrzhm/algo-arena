#include <bits/stdc++.h>

namespace sol1 {

class Solution {
 public:
  int minDistance(const std::string &word1, const std::string &word2) {
    int m = word1.size();
    int n = word2.size();
    // dp[i][j] 表示 word1[i..m-1] -> word2[j..n-1] 的最小操作次数
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    dp[m][n] = 0;
    for (int i = 0; i < m; ++i) dp[i][n] = m - i;  // word1[i..m-1] -> ""
    for (int j = 0; j < n; ++j) dp[m][j] = n - j;  // "" -> word2[j..n-1]

    for (int i = m - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
        if (word1[i] == word2[j]) {
          dp[i][j] = dp[i + 1][j + 1];  // 进行其它操作会使得结果变得更糟
        } else {
          dp[i][j] =
              std::min(dp[i][j + 1] /* insert */, std::min(dp[i + 1][j] /* delete */, dp[i + 1][j + 1] /* replace */)) +
              1;
        }
      }
    }

    return dp[0][0];
  }
};

}  // namespace sol1

namespace sol2 {

class Solution {
 public:
  int minDistance(const std::string &word1, const std::string &word2) {
    int m = word1.size();
    int n = word2.size();
    // dp[i][j] 表示 word1[0..i-1] -> word2[0..j-1] 的最小操作次数
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    dp[0][0] = 0;
    for (int i = 1; i <= m; ++i) dp[i][0] = i;  // word1[0..i-1] -> ""
    for (int j = 1; j <= n; ++j) dp[0][j] = j;  // "" -> word2[0..j-1]

    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (word1[i - 1] == word2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1];  // 进行其它操作会使得结果变得更糟
        } else {
          /**
           * insert: word1[0..i-1] -> word2[0..j-2], then insert words2[j - 1] to words1
           * delete: word1[0..i-2] -> word2[0..j-1], then delete words1[i - 1]
           * replace: word1[0..i-2] -> word2[0..j-2], then replace words1[i - 1] with words2[j - 1]
           */
          dp[i][j] = std::min(dp[i][j - 1], std::min(dp[i - 1][j], dp[i - 1][j - 1])) + 1;
        }
      }
    }

    return dp[m][n];
  }
};

}  // namespace sol2