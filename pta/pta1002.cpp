#include <bits/stdc++.h>

#define eps 1e-1

int main() {
  std::map<int, double> poly;

  int k;
  int n;
  double an;
  std::cin >> k;
  
  for (int i = 0; i < k; i++) {
    std::cin >> n >> an;
    poly[n] = an;
  }

  std::cin >> k;
  for (int i = 0; i < k; i++) {
    std::cin >> n >> an;
    if (poly.find(n) == poly.end()) {
      poly[n] = an;
    } else {
      poly[n] += an;
    }
  }

  int size = 0;
  for (auto &[_n, _an] : poly) {
    if (std::abs(_an - 0.0) < eps) {
      continue;
    }
    size++;
  }
  std::cout << size;
  for (auto it = poly.rbegin(); it != poly.rend(); ++it) {
    const auto &[_n, _an] = *it;
    if (std::abs(_an - 0.0) < eps) {
      continue;
    }
    // std::cout << " " << _n << " " << _an;
    printf(" %d %.1lf", _n, _an);
  }

  std::cout << std::endl;
  return 0;
}