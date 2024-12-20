/// 数字三角形
#include <bits/stdc++.h>

#define MAXN 1000001

// 索引为idx的数在所在的行中排第几个
static inline int GetNth(int idx, int row) {
  int x = ((row - 1) * row) >> 1;
  return idx - x;
}

// 第row行的第i个数的左孩子索引
static inline int LeftIdx(int i, int row) {
  int x = ((row + 1) * row) >> 1;
  return x + i;
}

static inline int GetLeft(int idx, int row) {
  return LeftIdx(GetNth(idx, row), row);
}

// 1 .. (r+1)*r/2
int nums[MAXN];
int sums[MAXN];
int opt[MAXN];
int rows;

int main() {
  std::cin >> rows;
  int idx = 1;
  for (int i = 1; i <= rows; i++) {
    for (int j = 1; j <= i; j++) {
      std::cin >> nums[idx++];
    }
  }

  --idx;
  assert(idx == ((rows + 1) * rows) >> 1);

  int max_idx = idx;
  int cnt = 0;
  int row = rows;

  while (idx > 0) {
    // Calculate left_idx and right_idx : O(1)
    int left = GetLeft(idx, row);
    int right = left + 1;

    if (left > max_idx) {
      opt[idx] = 0;
    } else if (sums[left] > sums[right]) {
      opt[idx] = left;
    } else {
      opt[idx] = right;
    }

    sums[idx] = nums[idx] + sums[opt[idx]];
    
    --idx;
    ++cnt;
    if (cnt == row) {
      --row;
      cnt = 0;
    }
  }

  std::cout << sums[1] << std::endl;
}