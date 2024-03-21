#include <vector>

class Solution
{
public:
  int sumOfEncryptedInt(std::vector<int> &nums)
  {
    int sum = 0;
    for (int num : nums) {
      int len = 0;
      int max  = -1;
      // find max and len
      while (num > 0) {
        max   = std::max(num % 10, max);
        num /= 10;
        ++len;
      }

      // encode
      num = 0;
      while (len > 0) {
        num = num * 10 + max;
        --len;
      }
      sum += num;
    }
    return sum;
  }
};