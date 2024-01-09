#include <bits/stdc++.h>

void Knapsack(int n, const int w[], int v[], int W) {
  int dp[n + 1][W + 1];
  memset(dp, 0, sizeof(dp));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= W; ++j) {
      if (j < w[i]) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
      }
    }
  }
  std::cout << dp[n][W] << std::endl;
}
