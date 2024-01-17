#include <bits/stdc++.h>

class Solution {
 public:
  std::vector<std::string> letterCombinations(const std::string &digits) {
    std::vector<std::string> results;
    std::string str;
    std::function<void(int)> backtracking = [&](int step) {
      if (step == digits.size()) {
        results.emplace_back(str);
        return;
      }

      for (char c : mp[digits[step]]) {
        str.push_back(c);
        backtracking(step + 1);
        str.pop_back();
      }
    };
    if (!digits.empty()) {
      backtracking(0);
    }
    return results;
  }

 private:
  std::unordered_map<char, std::string> mp{{'2', "abc"}, {'3', "def"},  {'4', "ghi"}, {'5', "jkl"},
                                           {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};
};