#include <bits/stdc++.h>

// #define MONO_QUEUE
#define ST

constexpr auto MAXN = 1000000;
int a[MAXN];
int n, m;


std::deque<int> dq;
int
mono_queue_main()
{
    std::cin >> n >> m;
    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    for (int i = 0; i < n; i++) {
        while (!dq.empty() && a[dq.back()] > a[i]) dq.pop_back();
        dq.push_back(i);
        while (!dq.empty() && dq.front() <= i - m) dq.pop_front();
        if (i >= m - 1) std::cout << a[dq.front()] << "\n";
    }
    return 0;
}

constexpr auto MAXLGLEN = 20;
int dp[MAXN][MAXLGLEN];
int LOG2[MAXN];

void
st_init()
{
    LOG2[0] = -1;
    for (int i = 1; i < MAXN; i++)
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
st_main()
{
    std::cin >> n >> m;
    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    st_init();

    for (int i = 0; i + m - 1 < n; i++)
        std::cout << st_query(i, i + m - 1) << "\n";

    return 0;
}


int
main()
{
#ifdef ST
    return st_main();
#else
    return mono_queue_main();
#endif
}