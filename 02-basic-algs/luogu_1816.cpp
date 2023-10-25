#include <bits/stdc++.h>

constexpr auto MAXN = 100000;
constexpr auto MAXLGLEN = 20;
int a[MAXN];
int dp[MAXN][MAXLGLEN];
int LOG2[MAXN + 1];
int m, n;

void
st_init()
{
    LOG2[0] = -1;
    for (int i = 1; i <= MAXN; i++)
        LOG2[i] = LOG2[i >> 1] + 1;

    for (int i = 0; i < n; i++)
        dp[i][0] = a[i];

    int lglen = LOG2[n];
    for (int l = 1; l <= lglen; l++)
        for (int i = 0; i + (1 << l) - 1 < n; i++)
            dp[i][l] = std::min(dp[i][l - 1], dp[i + (1 << (l - 1))][l - 1]);
}

int
st_query(int left, int right)
{
    int lglen = LOG2[right - left + 1];
    return std::min(dp[left][lglen], dp[right - (1 << lglen) + 1][lglen]);
}


int
main()
{
    std::cin >> n >> m;
    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    st_init();

    while (m--) {
        int left, right;
        std::cin >> left >> right;
        std::cout << st_query(left - 1, right - 1) << " ";
    }
    return 0;
}