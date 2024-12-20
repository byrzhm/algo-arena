#include <bits/stdc++.h>

constexpr auto MAXN = 100005;
constexpr auto MAXLEN = 22;
int n, m;
int dp[MAXN][MAXLEN];
int a[MAXN];
int LOG2[MAXN];

static inline int
read()
{
	int x = 0, f = 1;
    char ch = getchar();
	while (ch < '0' || ch > '9') {
        if (ch=='-') 
            f = -1;
        ch = getchar();
    }
	while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
	return x * f;
}

void
st_init()
{
    LOG2[0] = -1;
    for (int i = 1; i <= MAXN; i++)
        LOG2[i] = LOG2[i >> 1] + 1;

    for (int i = 1; i <= n; i++)
        dp[i][0] = a[i];

    // int len = static_cast<int>(log2(n));
    int len = LOG2[n];
    for (int l = 1; l <= len; l++)
        for (int s = 1; s + (1 << l) <= n + 1; s++)
            // s, s + 1, s + 2, ..., s + (1 << l) - 1 : length = (1 << l)
            dp[s][l] = std::max(dp[s][l-1], dp[s + (1 << (l-1))][l-1]);
}

int
st_query(int left, int right)
{
    // int len = static_cast<int>(log2(right - left + 1));
    int len = LOG2[right - left + 1];
    return std::max(dp[left][len], dp[right - (1 << len) + 1][len]);
    // left, left + 1, left + 2, ..., left + (1 << len) - 1
    // right - ((1 << len) - 1), right - ((1 << len) - 2), ..., right
}

int
main()
{
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        a[i] = read();

    st_init();

    for (int i = 0; i < m; i++) {
        int left, right;
        left = read();
        right = read();
        std::cout << st_query(left, right) << "\n";
    }

    return 0;
}