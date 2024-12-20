#include <vector>

class Solution
{
public:
  long long maximumHappinessSum(std::vector<int> &happiness, int k)
  {
    std::sort(happiness.begin(), happiness.end(), std::greater<>());
    long long sum = 0;
    int count       = 0;
    while (count < k) {
      int temp = happiness[count] - count;
      ++count;
      if (temp <= 0)
        break;

      sum += temp;
    }
    return sum;
  }
};