/**
 * @file poj_3624_Charm-Bracelet.cpp
 * @author Hongming Zhu (zhm1019@qq.com)
 * @brief 0/1背包问题, 可以采用dp, 跳跃点, 或者回溯法解决, 这里使用回溯法, 注意剪枝策略
 * @date 2023-12-20
 */
#include <algorithm>
#include <iostream>

#define MAXN 4000
int n;          ///< 物品数量
int c;          ///< 背包容量
int bestv = 0;  ///< 当前最优解
int cw = 0;     ///< 当前载重量
int cv = 0;     ///< 当前价值

/**
 * @brief 物品结构体, 包含属性重量和价值
 */
struct Item {
  int weight_;
  int value_;
} items[MAXN];

/**
 * @brief 重载比较运算符, 用于排序
 * 
 * @param l 左操作数
 * @param r 右操作数
 * @return true 当左操作数的单位价值大于右操作数时返回true
 * @return false 当左操作数的单位价值小于等于右操作数时返回false
 */
bool operator>(const Item &l, const Item &r) {
  return static_cast<double>(l.value_) / l.weight_ > static_cast<double>(r.value_) / r.weight_;
}

/**
 * @brief 计算上界
 * 
 * @param step 当前步数
 * @return int 上界
 */
int bound(int step) {
  int cleft = c - cw;  // 剩余背包容量
  int b = cv;
  while (step < n && items[step].weight_ <= cleft) {
    cleft -= items[step].weight_;
    b += items[step].value_;
    ++step;
  }
  if (step < n) {  // 装满背包
    b += items[step].value_ * cleft / items[step].weight_;
  }
  return b;
}

/**
 * @brief 回溯法
 * 
 * @param step 当前步数
 */
void backtracking(int step) {
  if (step == n) {
    bestv = cv;
    return;
  }

  if (cw + items[step].weight_ <= c) {  // x[step] = 1
    cw += items[step].weight_;
    cv += items[step].value_;
    backtracking(step + 1);
    cw -= items[step].weight_;
    cv -= items[step].value_;
  }

  if (bound(step + 1) > bestv) {  // x[step] = 0
    backtracking(step + 1);
  }
}

/**
 * @brief 主函数
 * 
 * @return int 
 */
int main() {
  std::cin >> n >> c;
  for (int i = 0; i < n; i++) {
    std::cin >> items[i].weight_ >> items[i].value_;
  }

  std::sort(items, items + n, std::greater<>{});

  backtracking(0);
  std::cout << bestv << std::endl;
  return 0;
}