#include <bits/stdc++.h>

#define MAXN 100

int s[MAXN][MAXN];  ///< 记录最优解, s[i][j]表示从i到j的最优解
int m[MAXN][MAXN];  ///< 记录最优值, m[i][j]表示从i到j的最优值
int p[MAXN];        ///< 记录矩阵的维度
int n;              ///< 矩阵的个数

void matrix_chain() {
  for (int i = 1; i <= n; ++i) {
    m[i][i] = 0;  // 一个矩阵不需要乘法
  }
  for (int l = 2; l <= n; ++l) {                                 // l表示矩阵链的长度
    for (int i = 1; i <= n - l + 1; ++i) {                       // i表示矩阵链的起点
      int j = i + l - 1;                                         // j表示矩阵链的终点
      m[i][j] = INT_MAX;                                         // 初始化为最大值
      for (int k = i; k <= j - 1; ++k) {                         // k表示分割点
        int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];  // 计算最优值
        if (q < m[i][j]) {                                       // 如果最优值小于当前最优值
          m[i][j] = q;                                           // 更新最优值
          s[i][j] = k;                                           // 更新最优解
        }
      }
    }
  }
}

void traceback(int i, int j) {
  if (i == j) {
    std::cout << "A" << i;  // 如果i和j相等, 则输出Ai
  } else {
    std::cout << "(";
    traceback(i, s[i][j]);      // 递归输出左半部分
    traceback(s[i][j] + 1, j);  // 递归输出右半部分
    std::cout << ")";
  }
}

int main() {
  std::cin >> n;
  for (int i = 0; i <= n; ++i) {
    std::cin >> p[i];
  }

  matrix_chain();

  std::cout << m[1][n] << std::endl;
  traceback(1, n);
}