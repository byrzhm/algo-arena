#include <iostream>
#include <limits>

#define MAXM 100000
const int n = 2;
int m;
int a[n][MAXM];
int testcases;

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> testcases;

  while (testcases-- > 0) {
    std::cin >> m;
    for (auto &row : a) {
      for (int i = 0; i < m; ++i) {
        std::cin >> row[i];
      }
    }

    int ans  = std::numeric_limits<int>::max();
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < m; ++i)
      sum1 += a[0][i];

    for (int i = 0; i < m; ++i) {
      sum1 -= a[0][i];
      ans = std::min(ans, std::max(sum1, sum2));
      sum2 += a[1][i];
    }
    std::cout << ans << '\n';
  }

  return 0;
}