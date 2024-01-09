#include <bits/stdc++.h>

namespace sol1 {

int max_sub_sum(int n, const int *a) {
  int sum = 0;
  int b = 0;
  for (int i = 1; i <= n; i++) {
    if (b > 0) {
      b += a[i];
    } else {
      b = a[i];
    }
    if (b > sum) {
      sum = b;
    }
  }
  return sum;
}

} // namespace sol1

namespace sol2 {

int B; ///< B为子数组的起始点下标
int E; ///< E为子数组的终止点下标
int Max; ///< Max为最大子数组的和

void max_sub_sum(const int a[], int n) {
  int dp;  ///< dp为子数组的和
  int tmp; ///< tmp为子数组的起始点下标

  // 初始化
  dp = Max = a[n - 1];
  tmp = n - 1;
  B = n - 1;
  E = n - 1;

  for (int i = n - 2; i >= 0; i--) { // 从右向左扫描
    if (dp > 0) { // 如果dp大于0，则继续累加
      dp += a[i];
    } else { // 否则，重新开始计算dp
      dp = a[i];
      tmp = i;
    }
    if (dp >= Max) {
      B = i;
      E = tmp;
      Max = dp;
    }
  }
}

} // namespace sol2 

int a[100000];
int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  std::cout << sol1::max_sub_sum(n, a) << '\n';
  sol2::max_sub_sum(a, n);
  std::cout << sol2::Max << '\n';
  std::cout << sol2::B << '\n';
  std::cout << sol2::E << std::endl;
  return 0;
}