#include <bits/stdc++.h>


std::vector<int> GrayCode(int n) {
  std::vector<int> res{0};
  std::bitset<16> gray_code{0};
  std::unordered_map<int, bool> map{{0, true}};
  bool valid = false;
  int len = static_cast<int>(pow(2, n));
  std::function<void(int)> backtracking = [&](int step) {
    if (step == len) {
      valid = true;
      return;
    }

    for (int i = 0; i < n && !valid; ++i) {
      gray_code.flip(i);
      int num = gray_code.to_ulong();
      if (map.find(num) == map.end()) {
        res.emplace_back(num);
        map[num] = true;
        backtracking(step + 1);
      }
      gray_code.flip(i);
    }

  };
  backtracking(0);
  return res;
}