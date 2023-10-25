#include <bits/stdc++.h>

constexpr auto MAXN = 15;
int weights[MAXN][MAXN];
int n, k;



int main()
{
    std::cin >> n >> k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            std::cin >> weights[i][j];
}