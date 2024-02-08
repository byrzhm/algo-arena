#include <bits/stdc++.h>

/**
 * Z Algorithm
 *   https://www.youtube.com/watch?v=CpZh4eF8QBw
 *   https://www.geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/
 *   https://oi-wiki.org/string/z-func/
 */

class Solution
{
public:
  int minimumTimeToInitialState(const std::string &word, int k)
  {
    int n    = word.size();
    auto z   = getZarr(word);
    int time = 1;
    for (int i = k; i < n; i += k, ++time) {
      if (z[i] == n - i)
        return time;
    }
    return time;
  }

private:
  std::vector<int> getZarr(const std::string &str)
  {
    int n = str.length();
    std::vector<int> z(n);
    int l = 0;
    int r = 0;
    for (int i = 1; i < n; ++i) {
      if (i > r) {
        l = r = i;
        while (r < n && str[r - l] == str[r])
          ++r;
        z[i] = r - l;
        --r;
      } else {
        int k = i - l;
        if (z[k] < r - i + 1) {
          z[i] = z[k];
        } else {
          l = i;
          while (r < n && str[r - l] == str[r])
            ++r;
          z[i] = r - l;
          --r;
        }
      }
    }
    return z;
  }
};