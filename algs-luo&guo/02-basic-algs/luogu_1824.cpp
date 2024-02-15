#include <bits/stdc++.h>

constexpr auto MAXN = 100000;
int x[MAXN];

int
cownum(int n, int target)
{
    int64_t base = x[0];
    int pos = std::lower_bound(x + 1, x + n, target + base) - x;
    int num = 1;

    while (pos != n) {
        num++;
        // printf("num=%d, pos=%d, x[pos]=%d\n", num, pos, x[pos]);
        base = x[pos];
        pos = std::lower_bound(x + pos + 1, x + n, target + base) - x;
    }

    return num;
}

int
main()
{
    int n, c;
    int left, right, mid;
    int min, max;
    std::cin >> n >> c;

    for (int i = 0; i < n; i++)
        std::cin >> x[i];

    std::sort(x, x + n);
    max = x[n-1] - x[0];
    min = INT32_MAX;
    for (int i = 1; i < n; i++)
        min = std::min(min, x[i] - x[i-1]);
    // let min = 0 is ok
    
    left = min, right = max;

    while (left < right) {
        mid = left + (right - left + 1)/2;
        // printf("left=%d, mid=%d, right=%d\n", left, mid, right);
        if (cownum(n, mid) < c) {
            right = mid - 1;
        } else {
            left = mid;
        }
    }

    std::cout << left << std::endl;

    return 0;
}