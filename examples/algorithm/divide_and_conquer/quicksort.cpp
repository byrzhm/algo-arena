#include <bits/stdc++.h>

int partition(std::vector<int> &vec, int l, int r) {
  int i = l, j = r, pivot = vec[l + rand() % (r - l + 1)];
  while (i <= j) {
    while (vec[i] < pivot) ++i;
    while (vec[j] > pivot) --j;
    if (i <= j) {
      std::swap(vec[i], vec[j]);
      ++i;
      --j;
    }
  }
  return i;
}

void quicksort(std::vector<int> &vec, int l, int r) {
  if (l < r) {
    int pivot = partition(vec, l, r);
    quicksort(vec, l, pivot - 1);
    quicksort(vec, pivot, r);
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> vec(n);
  for (int i = 0; i < n; ++i) std::cin >> vec[i];
  quicksort(vec, 0, n - 1);
  for (int i = 0; i < n; ++i) std::cout << vec[i] << " ";
  std::cout << std::endl;
}