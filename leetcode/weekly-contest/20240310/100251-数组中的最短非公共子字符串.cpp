#include <string>
#include <vector>
#include <set>

class Solution
{
public:
  std::vector<std::string> shortestSubstrings(std::vector<std::string> &arr)
  {
    auto compareString = [](const std::string &lhs, const std::string &rhs) {
      if (lhs.size() != rhs.size()) {
        return lhs.size() < rhs.size();
      }
      return lhs < rhs;
    };

    int n = arr.size();
    std::vector<std::set<std::string, decltype(compareString)>> setVec(n);
    std::vector<std::string> result;

    for (int i = 0; i < n; ++i) {
      int len = arr[i].length();
      for (int l = 0; l < len; ++l) {
        for (int r = l; r < len; ++r) {
          setVec[i].emplace(arr[i].substr(l, r - l + 1));
        }
      }
    }

    for (int i = 0; i < n; ++i) {
      bool repeat = false;
      for (auto &str : setVec[i]) {
        repeat = false;
        for (int j = 0; j < n; ++j) {
          if (j != i) {
            if (setVec[j].count(str) > 0) {
              repeat = true;
              break;
            }
          }
        }
        if (!repeat) {
          result.emplace_back(str);
          break;
        }
      }
      if (repeat) {
        result.emplace_back("");
      }
    }

    return result;
  }
};
