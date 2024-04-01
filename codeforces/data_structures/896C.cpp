/**
 * Willem, Chtholly and Seniorious
 * https://codeforces.com/problemset/problem/896/C
 * 
 * 区间加, 区间赋值, 区间第k小, 随机访问
 * 
 */

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <vector>

int n, m;
int64_t seed;
int64_t vmax;

int64_t Rng()
{
  int64_t ret = seed;
  seed        = (seed * 7 + 13) % 1000000007;
  return ret;
}

/**
 * @brief 带模运算的快速幂
 */
int64_t Power(int64_t base, int64_t exp, int64_t mod)
{
  base           %= mod;
  int64_t result  = 1;
  do {
    if ((exp & 1) != 0)
      (result *= base) %= mod;
    (base *= base) %= mod;
  } while ((exp >>= 1) != 0);
  return result;
}

std::map<int, int64_t> A;

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m >> seed >> vmax;

  /**
   * std::map<Key,T,Compare,Allocator>::insert
   * https://en.cppreference.com/w/cpp/container/map/insert
   */

  // 以 std::map 代替数组
  for (int i = 1; i <= n; ++i)
    A.insert(A.end(), std::make_pair(i, Rng() % vmax + 1));
  A.insert(A.end(), std::make_pair(n + 1, 0));

  for (int i = 1; i <= m; ++i) {
    int op = (Rng() % 4) + 1;
    int l  = (Rng() % n) + 1;
    int r  = (Rng() % n) + 1;
    int x, y;

    if (l > r)
      std::swap(l, r);

    if (op == 3)
      x = (Rng() % (r - l + 1)) + 1;
    else
      x = (Rng() % vmax) + 1;

    if (op == 4)
      y = (Rng() % vmax) + 1;

    auto it_l(--A.upper_bound(l));      // [l, r]
    if (it_l->first != l)               // l 不存在
      A[l] = it_l->second, ++it_l;      // it_l->first == l

    auto it_r(--A.upper_bound(r + 1));  // [l, r]
    if (it_r->first != r + 1)           // r + 1 不存在
      A[r + 1] = it_r->second, ++it_r;  // it_r->first == r + 1


    switch (op) {
      static std::vector<std::pair<int64_t, int>> v;
      static int64_t res;

      case 1:
        while (it_l != it_r) {
          (it_l++)->second += x;
        }
        break;

      case 2:
        while (it_l != it_r) {
          A.erase(it_l++);  // [l, r] 替换为 l
        }
        A[l] = x;
        break;

      case 3:
        v.clear();
        while (it_l != it_r) {
          int ub = (it_r--)->first;
          v.emplace_back(it_r->second, ub - it_r->first);
        }
        std::sort(v.begin(), v.end());
        for (int i = 0, cnt = 0;; ++i) {
          cnt += v[i].second;
          if (x <= cnt) {
            std::cout << v[i].first << '\n';
            break;
          }
        }
        break;

      case 4:
        res = 0;
        while (it_l != it_r) {
          int ub  = (it_r--)->first;
          res    += Power(it_r->second, x, y) * (ub - it_r->first);
          res    %= y;
        }
        std::cout << res << '\n';
      default:
        break;
    }
  }

  return 0;
}