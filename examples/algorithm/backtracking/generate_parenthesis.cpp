#include <bits/stdc++.h>

std::vector<std::string> generate_parenthesis(int n) {
  std::vector<std::string> res;
  std::function<void(int, int, std::string)> backtracking = [&](int left, int right, const std::string& paren_str) {
    if (left == right && left == n) {
      res.push_back(paren_str);
      return;
    }

    if (left >= right && left < n) {
      backtracking(left + 1, right, paren_str + '(');
    }
    
    if (right < left) {
      backtracking(left, right + 1, paren_str + ')');
    }
  };
  backtracking(0, 0, "");
  return res;
}

int main() {
  auto strings = generate_parenthesis(3);
  for (auto & str : strings) {
    std::cout << str << "\n";
  }
}