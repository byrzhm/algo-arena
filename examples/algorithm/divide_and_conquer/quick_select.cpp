#include <bits/stdc++.h>

int partition(std::vector<int> &vec, int l, int r) {
  int i = l, j = r, pivot = vec[l + rand() % (r - l + 1)];
  for (;;) {
    while (vec[i] < pivot) ++i;
    while (vec[j] > pivot) --j;
    if (i >= j) return j;
    std::swap(vec[i++], vec[j--]);
  }
}

int quick_select(std::vector<int> &vec, int l, int r, int k) {
  if (l == r) return vec[l];
  int pivot = partition(vec, l, r);
  if (pivot - l + 1 >= k) return quick_select(vec, l, pivot, k);
  return quick_select(vec, pivot, r, k - (pivot - l));
}

int main() {
  int n, k;
  std::cin >> n >> k;
  std::vector<int> vec(n);
  for (int i = 0; i < n; ++i) std::cin >> vec[i];
  std::cout << quick_select(vec, 0, n - 1, k) << std::endl;
}