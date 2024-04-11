#include <bits/stdc++.h>

int a[200005];

int
main()
{
    int64_t ans;
    int n, c;
    int p, l, r;
    std::cin >> n >> c;
    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    std::sort(a, a + n);
    
    ans = 0;
    l = r = 1;
    for (p = 0; p < n - 1; p++) {
        while (r < n && a[r] - a[p] <= c) r++;
        while (l < n && a[l] - a[p] < c) l++;
        // printf("l=%d, r=%d\n", l, r);
        ans += r - l;
    }
    std::cout << ans << std::endl;
    return 0;
}