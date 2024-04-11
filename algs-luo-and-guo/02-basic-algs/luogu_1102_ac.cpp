#include <bits/stdc++.h>

int a[200005];

int
main()
{
    int n, c;
    int64_t ans;
    std::cin >> n >> c;
    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    ans = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1 ; j < n; j++) {
            if (abs(a[j] - a[i]) == c)
                ans++;
        }
    }

    std::cout << ans << std::endl;
    return 0;
}