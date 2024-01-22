#include <bits/stdc++.h>

/**
 * 考虑以第 i 个字符为终点的最大长度 dp[i]:
 *     if s[i] == '(' then dp[i] = 0;
 *     if s[i] == ')' then ?
 *
 * 直觉:
 *     匹配后的括号可以看成一个整体
 *     右括号总是与最近的左括号相匹配
 *     匹配之后, 最大长度还要往前看
 *     如果往前看是左括号, 那么最大长度就确定了
 *     但是如果向前看是 dp 值大于 0 的右括号, 那么应该再加上去
 *     (不需要重复这一步骤, 如果我们"之前"已经这么处理了)
 */
class Solution {
 public:
  int longestValidParentheses(const std::string &s) {
    if (s.empty()) {
      return 0;
    }

    int maxLen;
    std::vector<int> dp(s.size());
    maxLen = dp[0] = 0;

    for (int i = 1; i < s.size(); ++i) {
      if (s[i] == '(') {
        dp[i] = 0;
      } else {  // s[i] == ')'
        int j = i - 1;
        // while (j >= 0 && dp[j] != 0) {
        j = j - dp[j];
        // }

        if (j < 0 || s[j] == ')') {
          dp[i] = 0;
        } else /* if (s[j] == '(') */ {
          // if (j > 0 && dp[j - 1] > 0) {
          //   dp[i] = dp[j - 1] + i - j + 1;
          // } else {  // j == 0 or dp[j - 1] == 0
          //   dp[i] = i - j + 1;
          // }
          dp[i] = (j > 0) ? dp[j - 1] + i - j + 1 : i - j + 1;
        }
      }
      maxLen = std::max(maxLen, dp[i]);
    }
    return maxLen;
  }
};

int main() {
  std::cout << Solution().longestValidParentheses("(()") << std::endl;
  std::cout << Solution().longestValidParentheses(")()())") << std::endl;
  std::cout << Solution().longestValidParentheses("") << std::endl;
  std::cout << Solution().longestValidParentheses("())") << std::endl;
}
