#include <bits/stdc++.h>

constexpr auto MAXN = 50005;
constexpr auto MAXLEN = 22;
int low[MAXN][MAXLEN];
int high[MAXN][MAXLEN];
int LOG2[MAXN];
int a[MAXN];
int n, q, len;

void
st_init()
{
    // 不用系统 log2 函数, 自己算
    LOG2[0] = -1;
    for (int i = 1; i <= MAXN; i++)
        LOG2[i] = LOG2[i>>1] + 1;

    for (int i = 1; i <= n; i++) {
        low[i][0] = a[i];
        high[i][0] = a[i];
    }

    int p = LOG2[n];  // 可倍增区间的最大次方: 2^p <= n
    for (int k = 1; k <= p; k++) // 倍增计算小区间, 先算小区间, 再算大区间, 逐步递推
        for (int s = 1; s + (1<<k) <= n+1; s++) {
            low[s][k] = std::min(low[s][k-1], low[s + (1<<(k-1))][k-1]);
            high[s][k] = std::max(high[s][k-1], high[s + (1<<(k-1))][k-1]);
        }
}

int
st_query(int L, int R)
{
    int k = LOG2[R - L + 1];
    int x = std::max(high[L][k], high[R - (1<<k) + 1][k]);
    int y = std::min(low[L][k], low[R - (1<<k) + 1][k]);
    return x - y;
}

int main()
{
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];

    st_init();

    for (int i = 1; i <= q; i++) {
        int L, R;
        std::cin >> L >> R;
        std::cout << st_query(L, R) << "\n";
    }
    return 0;
}