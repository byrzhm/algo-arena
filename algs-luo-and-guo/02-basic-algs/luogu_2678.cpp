#include <bits/stdc++.h>

constexpr auto MAXN = 50002;
int d[MAXN];

bool
rockcheck(int n, int m, int mind)
{
    int delNum = 0;
    int i = 1;
    int pred = 0, curd;

    while (i <= n) {
        curd = d[i];
        if (curd - pred < mind) {
            delNum++;
            i++;
        } else {
            pred = curd;
            i++;
        }
    }

    return delNum <= m;
}

int
main()
{
    int l, n, m;
    std::cin >> l >> n >> m;

    for (int i = 1; i <= n; i++)
        std::cin >> d[i];
    d[++n] = l;
    
    int left = 0, right = l;

    while (left < right) {
        int mid = left + (right - left + 1) / 2;
        // printf("left=%d, mid=%d, right=%d\n", left, mid, right);
        if (rockcheck(n, m, mid))
            left = mid;
        else
            right = mid - 1;
    }
    
    std::cout << left << std::endl;

    return 0;
}