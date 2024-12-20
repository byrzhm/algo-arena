/**
 * IOI 1999 -- luogu_1854/poj_1157
 * 花店橱窗布置 LITTLE SHOP OF FLOWERS
 */
#include <iostream>
#include <stack>

#define MAXN 101

/// dp[i][j]:
///     第i捆花束放在第j个花瓶中时, 1,...,i 捆花束的最大美学值总和
/// 转移方程:
///     dp[i][j] = value[i][j] + max{dp[i-1][1],..., dp[i-1][j-1]}
int dp[MAXN][MAXN];
int value[MAXN][MAXN];
int bunches, vases;

/// trace[i][j] :
///     1,...,i 捆花束取得美学和最大值, 并且第i捆花束放在第j号花瓶中时, 第i-1捆花束应该放在的位置
int trace[MAXN][MAXN];

//// 调试使用
// void PrintMat(int mat[][MAXN]) {
//   for (int i = 1; i <= bunches; i++) {
//     for (int j = 1; j <= vases; j++) {
//       std::cout << mat[i][j] << " ";
//     }
//     std::cout << std::endl;
//   }
// }

void GetInput() {
  std::cin >> bunches >> vases;
  for (int i = 1; i <= bunches; i++) {
    for (int j = 1; j <= vases; j++) {
      std::cin >> value[i][j];
    }
  }
}

void Init() {
  for (int i = 1; i <= bunches; i++) {
    for (int j = 1; j <= vases; j++) {
      dp[i][j] = -0x3f3f3f3f;
    }
  }
}

int Solve() {
  for (int j = 1; j <= vases - (bunches - 1); j++) {
    dp[1][j] = value[1][j];
  }

  for (int i = 2; i <= bunches; i++) {
    // 第i捆花束只能放在花瓶 i ~ V-(F-i) 之间
    for (int j = i; j <= vases - (bunches - i); j++) {
      int max = -0x3f3f3f3f;
      dp[i][j] = value[i][j];
      for (int k = 1; k <= j - 1; k++) {
        if (dp[i - 1][k] > max) {
          max = dp[i - 1][k];
          trace[i][j] = k;
          // printf("trace[%d]=%d dp[%d][%d]=%d\n", i - 1, k, i - 1, k, dp[i-1][k]);
        }
      }
      dp[i][j] += max;
    }
  }

  int max = -0x3f3f3f3f;
  for (int j = bunches; j <= vases; j++) {
    if (dp[bunches][j] > max) {
      max = dp[bunches][j];
      trace[bunches + 1][vases + 1] = j;
    }
  }
  return max;
}


void Ouput(int max) {
  std::cout << max << std::endl;
  std::stack<int> output_stack;
  int t = trace[bunches + 1][vases + 1]; // 最后一朵花应该放置的位置
  int i = bunches;
  while (t != 0) {
    output_stack.emplace(t);
    t = trace[i--][t];
  }
  for (int i = 1; i <= bunches; i++) {
    int t = output_stack.top();
    output_stack.pop();
    std::cout << t << (i == bunches ? "\n" : " ");
  }
}

int main() {
  GetInput();
  Init();
  Ouput(Solve());
}