#include <bits/stdc++.h>

class Solution
{
public:
  long long sumScores(const std::string &s)
  {
    auto z        = getZarr(s);
    long long ans = 0;
    for (int num : z) {
      ans += num;
    }
    return ans;
  }

private:
  std::vector<int> getZarr(const std::string &s)
  {
    int n = s.length(), l = 0, r = 0;
    std::vector<int> z(n);
    z[0] = n;

    for (int i = 1; i < n; ++i) {
      if (i > r) {
        l = r = i;
        while (r < n && s[r - l] == s[r])
          ++r;
        z[i] = r - l;
        --r;
      } else {
        int k = i - l;
        if (z[k] < r - i + 1) {
          z[i] = z[k];
        } else {
          l = i;
          while (r < n && s[r - l] == s[r])
            ++r;
          z[i] = r - l;
          --r;
        }
      }
    }
    return z;
  }
};