#include <algorithm>
#include <iostream>
#include <vector>

class Solution
{
public:
  std::vector<std::vector<int>> merge(std::vector<std::vector<int>> &intervals)
  {
    auto comparator = [](std::vector<int> &l, std::vector<int> &r) {
      if (l.front() != r.front())
        return l.front() < r.front();
      return l.back() < r.back();
    };

    std::sort(intervals.begin(), intervals.end(), comparator);
    std::vector<std::vector<int>> ans;

    int prevEnd = -1;
    for (auto &inter : intervals) {
      if (inter.front() > prevEnd) {
        ans.emplace_back(inter);
        prevEnd = inter.back();
      } else {
        ans.back().back() = std::max(inter.back(), prevEnd);
        prevEnd = ans.back().back();
      }
    }

    return ans;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // intervals = [[1,3],[2,6],[8,10],[15,18]]
  // {
  //   std::vector<std::vector<int>> intervals = {
  //       {1, 3},
  //       {2, 6},
  //       {8, 10},
  //       {15, 18}
  //   };
  //   for (auto &inter : Solution().merge(intervals)) {
  //     for (auto it : inter) {
  //       std::cout << ' ' << it;
  //     }
  //     std::cout << '\n';
  //   }
  // }

  // {
  //   std::vector<std::vector<int>> intervals = {
  //       {1, 4},
  //       {0, 4}
  //   };
  //   for (auto &inter : Solution().merge(intervals)) {
  //     for (auto it : inter) {
  //       std::cout << ' ' << it;
  //     }
  //     std::cout << '\n';
  //   }
  // }

  // {
  //   std::vector<std::vector<int>> intervals = {
  //       {1, 4},
  //       {2, 3}
  //   };
  //   for (auto &inter : Solution().merge(intervals)) {
  //     for (auto it : inter) {
  //       std::cout << ' ' << it;
  //     }
  //     std::cout << '\n';
  //   }
  // }

  {
    std::vector<std::vector<int>> intervals = {
        {1, 4},
        {0, 2},
        {3, 5}
    };
    for (auto &inter : Solution().merge(intervals)) {
      for (auto it : inter) {
        std::cout << ' ' << it;
      }
      std::cout << '\n';
    }
  }

  return 0;
}