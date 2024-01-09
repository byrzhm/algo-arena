#include <bits/stdc++.h>

struct Item {
  float weight;  ///< 物品重量
  int value;     ///< 物品价值
};

struct Node {
  int level;     ///< 节点所在的层
  int profit;    ///< 节点所在的层的价值
  int bound;     ///< 节点的价值上界
  float weight;  ///< 节点所在的层的重量
};

// 比较函数，按照单位重量价值从大到小排序
bool cmp(Item a, Item b) {
  double r1 = static_cast<double>(a.value) / a.weight;
  double r2 = static_cast<double>(b.value) / b.weight;
  return r1 > r2;
}

// 计算节点的价值上界
int bound(Node u, int n, int W, Item arr[]) {
  if (u.weight >= W) return 0;  // 超过背包容量，价值为0

  int profit_bound = u.profit;  ///< 价值上界

  int j = u.level + 1;       ///< 下一个节点的层
  int totweight = u.weight;  ///< 下一个节点的重量

  // 贪心法计算价值上界
  while ((j < n) && (totweight + arr[j].weight <= W)) {
    totweight += arr[j].weight;
    profit_bound += arr[j].value;
    j++;
  }

  // 装满背包
  if (j < n) profit_bound += (W - totweight) * arr[j].value / arr[j].weight;

  return profit_bound;
}

// 0-1背包问题的分支限界法
int knapsack(int W, Item arr[], int n) {
  // 按照单位重量价值从大到小排序
  std::sort(arr, arr + n, cmp);

  std::queue<Node> Q;  ///< 队列
  Node u, v;           ///< 节点

  // 根节点
  u.level = -1;
  u.profit = u.weight = 0;
  Q.push(u);

  int maxProfit = 0;
  while (!Q.empty()) {
    u = Q.front();
    Q.pop();

    if (u.level == -1) v.level = 0;

    if (u.level == n - 1) continue;

    v.level = u.level + 1;  // 下一个节点的层

    // 下一个节点的重量和价值
    v.weight = u.weight + arr[v.level].weight;
    v.profit = u.profit + arr[v.level].value;

    if (v.weight <= W && v.profit > maxProfit) maxProfit = v.profit;

    // 计算价值上界
    v.bound = bound(v, n, W, arr);

    // 如果价值上界大于当前最大价值，则将该节点插入队列
    if (v.bound > maxProfit) Q.push(v);

    // 做相同的事情, 但是不装下一个物品
    v.weight = u.weight;
    v.profit = u.profit;
    v.bound = bound(v, n, W, arr);
    if (v.bound > maxProfit) Q.push(v);
  }

  return maxProfit;
}

int main() {
  int W = 10;  // 背包容量
  Item arr[] = {{2, 40}, {3.14, 50}, {1.98, 100}, {5, 95}, {3, 30}};
  int n = sizeof(arr) / sizeof(arr[0]);

  std::cout << "Maximum possible profit = " << knapsack(W, arr, n) << std::endl;

  return 0;
}
