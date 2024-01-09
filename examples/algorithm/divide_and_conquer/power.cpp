#include <bits/stdc++.h>

uint64_t power(uint64_t x, uint64_t n) {
  if (n == 0) return 1;
  if (n == 1) return x;
  if (n % 2 == 0) return power(x * x, n / 2);
  return power(x * x, n / 2) * x;
}

int main() {
  uint64_t x, n;
  std::cin >> x >> n;
  std::cout << power(x, n) << std::endl;
}