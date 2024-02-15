#include <bits/stdc++.h>

std::vector<int> getZarr(const std::string &str)
{
  int n = str.length();
  std::vector<int> z(n);
  z[0]      = n;
  int left  = 0;
  int right = 0;

  for (int i = 1; i < n; ++i) {
    if (i > right) {
      left = right = i;
      while (right < n && str[right - left] == str[right])
        ++right;
      z[i] = right - left;
      --right;
    } else {
      int k = i - left;

      if (z[k] < right - i + 1) {
        z[i] = z[k];
      } else {
        left = i;
        while (right < n && str[right - left] == str[right])
          ++right;
        z[i] = right - left;
        --right;
      }
    }
  }

  return z;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string a;
  std::string b;

  std::cin >> a >> b;

  std::string concat = b + "$" + a;
  auto z1            = getZarr(b);
  auto z2            = getZarr(concat);

  int64_t ans1       = 0;
  int64_t ans2       = 0;

  for (int i = 1, j = 0; j < z1.size(); ++i, ++j) {
    ans1 = ans1 ^ (i * static_cast<int64_t>(z1[j] + 1));
  }

  for (int i = 1, j = b.size() + 1; j < z2.size(); ++i, ++j) {
    ans2 = ans2 ^ (i * static_cast<int64_t>(z2[j] + 1));
  }

  std::cout << ans1 << '\n'
            << ans2 << '\n';
}