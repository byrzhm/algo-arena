#include <cstdint>
#include <iostream>

class Solution
{
public:
  double myPow(double x, int n)
  {
    int64_t N = n;
    if (N < 0)
      return 1.0 / quickPow(x, -N);

    return quickPow(x, N);
  }

private:
  double quickPow(double x, int64_t N)
  {
    if (N == 0)
      return 1.0;

    double y = quickPow(x, N >> 1);
    return N % 2 == 0 ? y * y : y * y * x;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout << Solution().myPow(2.0, 10) << '\n';
  std::cout << Solution().myPow(0.00001, 2147483647) << '\n';
  std::cout << Solution().myPow(1.0, -2147483648) << '\n';

  return 0;
}