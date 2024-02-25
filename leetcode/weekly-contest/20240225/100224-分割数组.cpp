#include <unordered_set>

class Solution
{
public:
  bool isPossibleToSplit(std::vector<int> &nums)
  {
    std::unordered_set<int> firstSet, secondSet;
    for (auto num : nums) {
      if (firstSet.count(num) == 0) {
        firstSet.emplace(num);
      } else if (secondSet.count(num) == 0) {
        secondSet.emplace(num);
      } else {
        return false;
      }
    }
    return true;
  }
};
