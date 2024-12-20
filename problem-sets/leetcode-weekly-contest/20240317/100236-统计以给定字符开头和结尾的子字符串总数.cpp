#include <string>

using std::string;

class Solution
{
public:
  long long countSubstrings(const string& s, char c)
  {
    long long cnt = 0;
    for (auto chr : s) {
      if (chr == c)
        ++cnt;
    }
    return cnt * (cnt + 1) / 2;
  }
};