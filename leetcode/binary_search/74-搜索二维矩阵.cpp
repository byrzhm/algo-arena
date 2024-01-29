#include <bits/stdc++.h>

class Solution {
 public:
  bool searchMatrix(std::vector<std::vector<int>> &matrix, int target) {
    // 加上捕获会快一点, 不知道为什么
    auto row = std::lower_bound(matrix.begin(), matrix.end(), target,
                                [&](std::vector<int> &row, int val) { return row[0] < val; });
    if (row != matrix.end() && (*row)[0] == target) return true;  // 这一行的第一个就是target

    if (row == matrix.begin()) return false;  // 前面没有行了, 并且这一行第一个不是target(>target)

    std::advance(row, -1);  // 在前一行寻找

    auto col = std::lower_bound(row->begin(), row->end(), target);

    return col != row->end() && *col == target;
  }
};