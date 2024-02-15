/**
 * IOI 1999 -- luogu_1854/poj_1157
 * 花店橱窗布置 LITTLE SHOP OF FLOWERS
 */
#include <iostream>
#include <deque>

#define MAXN 101

/// dp[i][j]:
///     前i捆花束放在前j个花瓶中的最大美学值和
int dp[MAXN][MAXN];
/// trace[i][j]:
///     前i捆花束放在前j个花瓶中取得最大美学值和时, 第i捆花束应该放在的花瓶号
int trace[MAXN][MAXN];
int value[MAXN][MAXN];
int bunches, vases;

/**
 * @brief 调试使用, 打印二维数组
 * @param mat 要打印的二维数组
 */
void PrintMat(int mat[][MAXN], const char* name) {
  // std::cout << name << ":" << std::endl;
  // for (int i = 1; i <= bunches; i++) {
  //   for (int j = 1; j <= vases; j++) {
  //     std::cout << mat[i][j] << " ";
  //   }
  //   std::cout << std::endl;
  // }
}

/**
 * @brief 获取输入
 */
void GetInput() {
  std::cin >> bunches >> vases;
  for (int i = 1; i <= bunches; i++) {
    for (int j = 1; j <= vases; j++) {
      std::cin >> value[i][j];
    }
  }
}

/**
 * @brief 解决方法
 */
void Solve() {
  /// 初始化 dp[1][j], trace
  dp[1][1] = value[1][1];
  trace[1][1] = 1;
  for (int j = 2; j <= vases - (bunches - 1); j++) {
    if (value[1][j] > dp[1][j - 1]) {
      dp[1][j] = value[1][j];
      trace[1][j] = j;
    } else {
      dp[1][j] = dp[1][j - 1];
      trace[1][j] = trace[1][j - 1];
    }
  }

  ///
  /// 转移方程:
  /// if j == i:
  ///     dp[i][j] = dp[i][i]
  ///                value[i][i] + dp[i - 1][i - 1]
  /// if j > i:    
  ///     dp[i][j] = max{value[i][j] + dp[i - 1][j - 1],
  ///                    dp[i][j - 1]}
  /// 
  for (int i = 2; i <= bunches; i++) {
    dp[i][i] = value[i][i] + dp[i - 1][i - 1];
    trace[i][i] = i;
    for (int j = i + 1; j <= vases - (bunches - i); j++) {
      if (value[i][j] + dp[i - 1][j - 1] > dp[i][j - 1]) {
        dp[i][j] = value[i][j] + dp[i - 1][j - 1];
        trace[i][j] = j;
      } else {
        dp[i][j] = dp[i][j - 1];
        trace[i][j] = trace[i][j - 1];
      }
    }
  }
}

void Output() {
  int max = dp[bunches][vases];
  std::cout << max << "\n";

  std::deque<int> deque;
  int f = bunches;
  int v = vases;
  int t = trace[f][v];
  while (f > 0) {
    deque.emplace_front(t);
    --f;
    t = trace[f][t - 1];
  }
  for (int i = 0; i < bunches; i++) {
    std::cout << deque[i] << (i == bunches - 1 ? "\n" : " ");
  }
}

int main() {
  GetInput();
  Solve();
  Output();
  PrintMat(trace, "trace");
  PrintMat(dp, "dp");
}