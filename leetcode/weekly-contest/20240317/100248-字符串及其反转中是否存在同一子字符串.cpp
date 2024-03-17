#include <string>
#include <unordered_set>

using std::string;
using std::unordered_set;

class Solution
{
public:
  bool isSubstringPresent(const string &s)
  {
    unordered_set<string> set;
    int n = s.length();
    for (int i = 0; i < n - 1; ++i) {
      string rs = s.substr(i, 2);
      set.emplace(rs);
      reverse(rs.begin(), rs.end());
      if (set.count(rs) > 0) {
        return true;
      }
    }
    return false;
  }
};