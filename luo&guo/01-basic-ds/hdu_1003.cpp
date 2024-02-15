#include <bits/stdc++.h>

#define DP

// Method 1: greedy algorithm
#ifdef GREEDY
int
_main()
{
    int t, n, a;
    int maxsum, sum, start, end, p;

    if (scanf("%d", &t) != 1) {
        exit(-1);
    }
    for (int i = 1; i <= t; i++) {
        if (scanf("%d", &n) != 1) {
            exit(-1);
        }
        maxsum = INT_MIN;
        sum = 0;
        start = end = p = 1;
        for (int j = 1; j <= n; j++) {
            if (scanf("%d", &a) != 1) {
                exit(-1);
            }
            sum += a;
            if (sum > maxsum) {
                maxsum = sum;
                start = p;
                end = j;
            }
            if (sum < 0) {
                p = j + 1;
                sum = 0;
            }
        }
        printf("Case %d:\n%d %d %d\n", i, maxsum, start, end);
        if (i != t)
            std::cout << std::endl;
    }
    exit(0);
}
#endif

// Method 2: Dynamic Programming
#ifdef DP
int dp[100005];
int
_main()
{
    int t, n;
    int maxsum, start, end, p;
    if (scanf("%d", &t) != 1) {
        exit(-1);
    }
    for (int j = 0; j < t; j++) {
        if (scanf("%d", &n) != 1)
            exit(-1);
        for (int i = 0; i < n; i++)
            if (scanf("%d", &dp[i]) != 1)
                exit(-1);
        
        start = end = p = 0;
        maxsum = dp[0];

        for (int i = 1; i < n; i++) {
            if (dp[i] + dp[i-1] >= dp[i]) {
                dp[i] = dp[i] + dp[i-1];
            } else {
                p = i;
            }

            if (dp[i] > maxsum) {
                maxsum = dp[i];
                start = p;
                end = i;
            }
        }

        printf("Case %d:\n%d %d %d\n", j+1, maxsum, start+1, end+1);
        if (j != t-1)
            std::cout << std::endl;
    }
    exit(0);
}
#endif

int
main()
{
    _main();
    exit(0);
}