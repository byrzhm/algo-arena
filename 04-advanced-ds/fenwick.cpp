#include <bits/stdc++.h>

const int N = 1000;

int tree[N] = {0};

static inline int lowbit(int x) {
  // x 的二进制中，最低位的 1 以及后面所有 0 组成的数。
  // lowbit(0b01011000) == 0b00001000
  //          ~~~~^~~~
  // lowbit(0b01110010) == 0b00000010
  //          ~~~~~~^~
  return x & -x;
}

void update(int x, int d) {
  while (x <= N) {
    tree[x] += d;
    x += lowbit(x);
  }
}

int sum(int x) {
  int ans = 0;
  while (x > 0) {
    ans += tree[x];
    x -= lowbit(x);
  }
  return ans;
}

int a[11] = {0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

int main() {
  for (int i = 1; i <= 10; i++) {
    update(i, a[i]);
  }
  std::cout << "old: [5, 8]=" << sum(8) - sum(4) << std::endl;
  update(5, 100);
  std::cout << "new: [5, 8]=" << sum(8) - sum(4) << std::endl;
  return 0;
}