/**
 * Fenwick tree
 * 区间修改, 区间查询
 */

#include <bits/stdc++.h>

#define MAXN 100004
int64_t tree1[MAXN], tree2[MAXN];
int n;

static inline int lowbit(int x) {
  return x & -x;
}

void update(int idx, int64_t delta, int64_t *tree) {
  int i = idx;
  while (i <= n) {
    tree[i] += delta;
    i += lowbit(i);
  }
}

int64_t getsum(int idx, const int64_t *tree) {
  int i = idx;
  int64_t sum = 0;
  while (i > 0) {
    sum += tree[i];
    i -= lowbit(i);
  }
  return sum;
}

int main() {
  int m;
  if (scanf("%d %d", &n, &m) != 2) {
    exit(EXIT_FAILURE);
  }

  int64_t prev, curr;
  prev = 0;
  for (int i = 1; i <= n; i++) {
    if (scanf("%ld", &curr) != 1) {
      exit(EXIT_FAILURE);
    }
    update(i, curr - prev, tree1);
    update(i, (curr - prev) * i, tree2);
    prev = curr;
  }

  while ((m--) != 0) {
    int type, x, y;
    if (scanf("%d %d %d", &type, &x, &y) != 3) {
      exit(EXIT_FAILURE);
    }

    if (type == 1) { // 区间加
      int delta;
      if (scanf("%d", &delta) != 1) {
        exit(EXIT_FAILURE);
      }

      // [x, y] 区间加
      // d[x] += delta, d[y+1]  -= delta
      update(x, delta, tree1);
      update(y + 1, -delta, tree1);
      update(x, delta * x, tree2);
      update(y + 1, -(y + 1) * delta, tree2);

    } else { // 区间查询
      // ! wrong: int64_t sum1 = (x + 1) * getsum(x, tree1) - getsum(x, tree2);
      int64_t sum1 = x * getsum(x - 1, tree1) - getsum(x - 1, tree2);
      int64_t sum2 = (y + 1) * getsum(y, tree1) - getsum(y, tree2);
      std::cout << sum2 - sum1 << "\n";
    }
  }

  return 0;
}