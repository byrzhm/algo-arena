#include <bits/stdc++.h>

#define MAX  1005
int value[MAX];
int volume[MAX];
int dp[MAX + 1][MAX + 1];

int
solve(int n, int v)
{
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= v; j++) {
            if (volume[i] > j)
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - volume[i]] + value[i]);
        }
    }
    return dp[n][v];
}

int
main()
{
    int testNum;
    std::cin >> testNum;

    while (testNum--) {
        int n, v;
        std::cin >> n >> v;

        for (int i = 1; i <= n; i++)
            std::cin >> value[i];
        
        for (int i = 1; i <= n; i++)
            std::cin >> volume[i];

        std::cout << solve(n, v) << std::endl;
    }

    return 0;
}