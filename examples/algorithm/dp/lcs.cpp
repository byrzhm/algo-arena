#include <bits/stdc++.h>

#define MAXN 100

int m;              ///< x的长度
int n;              ///< y的长度
char x[MAXN];       ///< x的字符数组
char y[MAXN];       ///< y的字符数组
int c[MAXN][MAXN];  ///< 记录最优值, c[i][j]表示x[0:i]和y[0:j]的最优值
int b[MAXN][MAXN];  ///< 记录最优解, b[i][j]表示x[0:i]和y[0:j]的最优解

void LCSLength() {
  for (int i = 0; i <= m; ++i) {
    c[i][0] = 0;  // x[0:i]和y[0:0]的最优值为0
  }
  for (int j = 0; j <= n; ++j) {
    c[0][j] = 0;  // x[0:0]和y[0:j]的最优值为0
  }
  for (int i = 1; i <= m; ++i) {    // i表示x的长度
    for (int j = 1; j <= n; ++j) {  // j表示y的长度
      if (x[i - 1] == y[j - 1]) {   // 如果x[i - 1]和y[j - 1]相等
        c[i][j] = c[i - 1][j - 1] + 1;
        b[i][j] = 1;
      } else if (c[i - 1][j] >= c[i][j - 1]) {  // 如果x[i - 1]和y[j - 1]不相等, 且c[i - 1][j] >= c[i][j - 1]
        c[i][j] = c[i - 1][j];
        b[i][j] = 2;
      } else {  // 如果x[i - 1]和y[j - 1]不相等, 且c[i - 1][j] < c[i][j - 1]
        c[i][j] = c[i][j - 1];
        b[i][j] = 3;
      }
    }
  }
}

void PrintLCS(int i, int j) {
  if (i == 0 || j == 0) return;
  if (b[i][j] == 1) {
    PrintLCS(i - 1, j - 1);
    std::cout << x[i - 1];
  } else if (b[i][j] == 2) {
    PrintLCS(i - 1, j);
  } else {
    PrintLCS(i, j - 1);
  }
}

int main() {
  std::cin >> m >> n;
  for (int i = 0; i < m; ++i) {
    std::cin >> x[i];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> y[i];
  }

  LCSLength();

  std::cout << c[m][n] << std::endl;
  PrintLCS(m, n);
}