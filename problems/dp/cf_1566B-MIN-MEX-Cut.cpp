#include <iostream>
#include <algorithm>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int test;
  std::cin >> test;
  while (test-- > 0) {
    std::string s;
    std::cin >> s;
    int zeroes = std::count(s.begin(), s.end(), '0');
    if (zeroes == 0) {
      std::cout << 0 << '\n';
      continue;
    }

    int first = s.find('0');
    int last = s.rfind('0');
    if (last - first + 1 == zeroes) {
      std::cout << 1 << '\n';
    } else {
      std::cout << 2 << '\n';
    }
  }
  
  return 0;
}