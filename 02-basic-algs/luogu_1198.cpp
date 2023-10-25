#include <bits/stdc++.h>

constexpr auto MAXM = 200005;
constexpr auto MAXLG = 22;
int dp[MAXM][MAXLG];
int a[MAXM];
int end;
int opnum;
int64_t mod;
int prevq;

void
st_append(int x)
{
    a[end] = (mod + prevq + x) % mod;
    // printf("%d\n", a[end]);
    dp[end][0] = a[end];
    end++;
    int lglen = log2(end);
    for (int l = 1; l <= lglen; l++) {
        dp[end - (1 << l)][l] = 
            std::max(dp[end - (1 << l)][l - 1], 
                     dp[end - (1 << (l - 1))][l - 1]);
    }
}

int
st_query(int len)
{
    int lglen = log2(len);
    // printf("l=%d, len=%d, end=%d\n", l, len, end);
    // printf("dp[end - l][len]=%d, dp[end - (1 << len)][len]=%d\n", 
        // dp[end - l][len], dp[end - (1 << len)][len]);
    prevq = std::max(dp[end - len][lglen], dp[end - (1 << lglen)][lglen]);
    return prevq;
}

int
main()
{
    char op;
    int x;
    std::cin >> opnum >> mod;

    while (opnum--) {
        std::cin >> op >> x;
        if (op == 'A') {
            st_append(x);
        } else {
            std::cout << st_query(x) << '\n';
        }
    }
    return 0;
}