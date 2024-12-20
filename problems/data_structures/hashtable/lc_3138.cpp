#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class Solution
{
public:
  int minAnagramLength(const string &s)
  {
    int n      = s.length();
    auto check = [&](int m) {
      unordered_map<char, int> basetbl;
      for (auto c : s.substr(0, m))
        ++basetbl[c];
      for (int i = m; i < n; i += m) {
        unordered_map<char, int> tmptbl;
        for (int j = i; j < i + m; ++j) {
          tmptbl[s[j]] += 1;
          if (basetbl.count(s[j]) == 0 || basetbl[s[j]] < tmptbl[s[j]]) {
            // basetbl.count(s[j]) < tmptbl[s[j]] is false
            // basetbl[s[j]] < tmptbl[s[j]] is also false
            // why?
            return false;
          }
        }
        if (basetbl.size() != tmptbl.size())
          return false;
      }
      return true;
    };

    for (int i = 1; i < n; ++i) {
      if (n % i != 0) continue;
      if (check(i)) return i;
    }
    return n;
  }
};