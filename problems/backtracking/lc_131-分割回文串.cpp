#include <bits/stdc++.h>

class Solution {
 public:
  std::vector<std::vector<std::string>> partition(const std::string &s) {
    std::vector<std::vector<std::string>> results;
    std::vector<std::string> splits;
    auto isPalindrome = [&](int begin, int end) -> bool {
      for (; begin <= end && s[begin] == s[end]; ++begin, --end)
        ;
      return begin > end;
    };
    std::function<void(int)> backtracking = [&](int step) {
      if (step == s.size()) {  // 刚好分割完
        results.emplace_back(splits);
        return;
      }

      for (int i = step; i < s.size(); ++i) {
        if (isPalindrome(step, i)) {
          splits.push_back(s.substr(step, i - step + 1));
          backtracking(i + 1);  // 下一次分割起始点在 i + 1
          splits.pop_back();
        }
      }
    };
    backtracking(0);
    return results;
  }
};