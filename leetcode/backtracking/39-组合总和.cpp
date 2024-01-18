#include <bits/stdc++.h>

class Solution {
 public:
  std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates, int target) {
    std::sort(candidates.begin(), candidates.end());
    currSum = 0;
    backtracking(candidates, target, 0);
    return results;
  }

 private:
  void backtracking(std::vector<int> const &candidates, int target, int step) {
    // 先尽量装, 下面的循环结束后, currSum >= target
    while (currSum < target) {
      currSum = currSum + candidates[step];
      comb.push_back(candidates[step]);
    }

    // 如果 currSum = target, 记录下来
    if (currSum == target) {
      results.emplace_back(comb);
    }

    // 逐个 pop_back 并向下递归
    while (!comb.empty() && comb.back() == candidates[step]) {
      comb.pop_back();
      currSum = currSum - candidates[step];
      // 剪枝: 只有剩下的数足以放下下一个数(已排序)才递归
      if (step != candidates.size() - 1 && target - currSum >= candidates[step + 1]) {
        backtracking(candidates, target, step + 1);
      }
    }
  }

 private:
  int currSum;
  std::vector<int> comb;
  std::vector<std::vector<int>> results;
};

int main() {
  std::vector<int> candidates{2, 3, 6, 7};
  int target = 7;
  auto ans = Solution().combinationSum(candidates, target);
  return 0;
}
