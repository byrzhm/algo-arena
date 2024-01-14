#include <bits/stdc++.h>

class Solution {
 public:
  int longestConsecutive(std::vector<int> &nums) {
    std::unordered_set<int> set;

    for (auto num : nums) {
      set.insert(num);
    }

    int maxLen = 0;
    for (auto num : set) {                   // 应该使用去重后的set遍历, 而不是nums
      if (set.find(num - 1) == set.end()) {  // 只考虑最左的数
        int currLen = 1;
        int currNum = num;
        while (set.find(currNum + 1) != set.end()) {
          ++currLen;
          ++currNum;
        }
        maxLen = std::max(maxLen, currLen);
      }
    }

    return maxLen;
  }
};