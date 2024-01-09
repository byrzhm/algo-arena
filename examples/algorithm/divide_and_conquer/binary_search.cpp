#include <bits/stdc++.h>

int binary_search(const std::vector<int> &vec, int target) {
  int l = 0, r = vec.size() - 1;
  while (l <= r) {
    int mid = (l + r) / 2;
    if (vec[mid] == target) return mid;
    if (vec[mid] < target)
      l = mid + 1;
    else
      r = mid - 1;
  }
  return -1;
}

int main() {
  int n, target;
  std::cin >> n >> target;
  std::vector<int> vec(n);
  for (int i = 0; i < n; ++i) std::cin >> vec[i];
  std::cout << binary_search(vec, target) << std::endl;
}