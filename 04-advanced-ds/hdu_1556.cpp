/**
 * Fenwick tree
 * 区间修改, 单点查询
 * 
 * Color the ball
 * N个气球排成一排，从左到右依次编号为1,2,3....N.每次给定2个整数a b(a <= b),
 * lele便为骑上他的“小飞鸽"牌电动车从气球a开始到气球b依次给每个气球涂一次颜色。
 * 但是N次以后lele已经忘记了第I个气球已经涂过几次颜色了，你能帮他算出每个气球被涂过几次颜色吗？
 */
#include <bits/stdc++.h>

#define MAXN 100005
int tree[MAXN];
int n;

static inline int lowbit(int x) { return x & -x; }

void update(int idx, int delta) {
  int i = idx;
  while (i <= n) {
    tree[i] += delta;
    i += lowbit(i);
  }
}

int getsum(int idx) {
  int sum = 0;
  int i = idx;
  while (i > 0) {
    sum += tree[i];
    i-= lowbit(i);
  }
  return sum;
}

int main() {
  while (scanf("%d", &n) == 1) {
    if (n == 0) {
      break;
    }

    memset(tree, 0, (n + 1) * sizeof(int));
    for (int i = 0; i < n; i++) {
      int a, b;
      if (scanf("%d %d", &a, &b) != 2) {
        exit(EXIT_FAILURE);
      }
      // [a, b] 区间加 1
      // <=> d[a] 单点加 1, d[b+1] 单点减 1
      update(a, 1);
      update(b + 1, -1);
    }
    for (int i = 1; i <= n; i++) {
      std::cout << getsum(i) << (i == n ? "\n" : " ");
    }
  }
  return 0;
}