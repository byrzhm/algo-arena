#include <bits/stdc++.h>

int main() {
  int a, b, sum, sign;
  std::cin >> a >> b;

  sum = a + b;
  if (sum == 0) {
    std::cout << '0' << std::endl;
    return 0;
  }

  sign = (sum >= 0 ? 1 : -1);
  sum *= sign;

  int count = 0;
  std::deque<int> s;
  while (sum > 0) {
    int rem = sum % 10;
    sum /= 10;
    s.push_front(rem);
    if (++count % 3 == 0) {
      s.push_front(-1);
    }
  }

  if (s.front() == -1) {
    s.pop_front();
  }

  if (sign < 0) {
    std::cout << '-';
  }

  for (int &i : s) {
    std::cout << static_cast<char>(i == -1 ? ',' : '0' + (i - 0));
  }
  std::cout << std::endl;
  return 0;
}