#include <bits/stdc++.h>

class Solution
{
public:
  // 进行数次删除操作后使得剩余字符串是原字符串的前缀
  int minimumTimeToInitialState(const std::string &word, int k)
  {
    int n    = word.size();
    int time = 1;
    for (int i = k; i < n; i += k, ++time) {
      if (word.substr(i) == word.substr(0, n - i))  // 可以进行优化
        return time;
    }
    return time;
  }
};