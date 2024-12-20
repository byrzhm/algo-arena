#include <bits/stdc++.h>

namespace slow {

class Solution
{
public:
  std::vector<int> partitionLabels(const std::string &s)
  {
    int n = s.size();
    // TODO(有必要吗): 记录每个字母最早出现的位置与最晚出现的位置
    std::unordered_map<char, std::pair<int, int>> posmap;
    for (int i = 0; i < n; ++i) {
      if (posmap.count(s[i]) > 0) {
        posmap[s[i]].second = i;
      } else {
        posmap[s[i]] = {i, i};
      }
    }

    std::vector<int> partition;
    int begin = 0;
    int end   = 0;
    for (int i = 0; i < n; i++) {
      if (i <= end) {
        end = std::max(posmap[s[i]].second, end);
        if (i == end) {
          partition.emplace_back(end - begin + 1);
          begin = end = i + 1;
        }
      }
    }
    return partition;
  }
};

}  // namespace slow

namespace fast {

class Solution
{
public:
  // 观察到第一次出现的位置是不需要记录的
  std::vector<int> partitionLabels(const std::string &s)
  {
    int n = s.size();
    std::unordered_map<char, int> posmap;
    for (int i = 0; i < n; ++i) {
      posmap[s[i]] = i;
    }

    std::vector<int> partition;
    int begin = 0;
    int end   = 0;
    for (int i = 0; i < n; i++) {
      if (i <= end) {
        end = std::max(posmap[s[i]], end);
        if (i == end) {
          partition.emplace_back(end - begin + 1);
          begin = end = i + 1;
        }
      }
    }
    return partition;
  }
};

}  // namespace fast