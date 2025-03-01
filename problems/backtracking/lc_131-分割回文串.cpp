#include <functional>
#include <string>
#include <vector>
using std::function;
using std::string;
using std::vector;

// clang-format off
class Solution {
 public:
    vector<vector<string>> partition(const string &s) {
    vector<vector<string>> results;
    vector<string> splits;
    auto isPalindrome = [&](int begin, int end) -> bool {
      for (; begin <= end && s[begin] == s[end]; ++begin, --end)
        ;
      return begin > end;
    };
    function<void(int)> backtracking = [&](int step) {
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
// clang-format on
