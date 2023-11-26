#include <bits/stdc++.h>

#define MAX_ITEM_NUM 101
#define MAX_BAG_SIZE 1001

struct Item {
  int size;
  int value;
  explicit Item(int _size = 0, int _value = 0) : size(_size), value(_value) {}
};

std::vector<Item> items(1);
int bag_size, item_number;

/**
 * DP 状态
 * dp[i][j]表示把前i个物品(从第1个到第i个)装入容量为j的背包中获得的最大价值
 * 可以把每个dp[i][j]都看作一个背包: 背包容量为j, 装1~i这些物品 
 * 最后dp[N][C]就是问题的答案
 */
int dp[MAX_ITEM_NUM][MAX_BAG_SIZE];

void GetInput() {
  std::cin >> bag_size >> item_number;
  for (int i = 0; i < item_number; i++) {
    int item_size, item_value;
    std::cin >> item_size >> item_value;
    items.emplace_back(item_size, item_value);
  }
}

/**
 * 0/1 knapsack problem:
 *  dp[0][j] = 0
 *  dp[i][j] = m[i-1][j] if wi > j (the new item is more than the current weight limit)
 *  dp[i][j] = max{m[i-1][j], m[i-1][j - wi] + vi} if wi <= j
 */
void Knapsack() {
  for (int i = 1; i <= item_number; i++) {
    for (int j = 1; j <= bag_size; j++) {
      if (j >= items[i].size) {
        dp[i][j] = std::max(dp[i-1][j], dp[i-1][j-items[i].size] + items[i].value);
      } else {
        dp[i][j] = dp[i-1][j];
      }
    }
  }
}

void ShowDPMatrix() {
  for (int i = 0; i <= item_number; i++) {
    printf("i=%2d:", i);
    for (int j = 0; j <= bag_size; j++) {
      printf("  %2d", dp[i][j]);
    }
    printf("\n");
  }
}

int main() {
  GetInput();
  Knapsack();
  ShowDPMatrix();
  std::cout << dp[item_number][bag_size] << std::endl;
}
