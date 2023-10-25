#include <bits/stdc++.h>

constexpr auto MAX = 100001;
int64_t s[MAX];

int
divide(int n, int64_t target)
{
    // printf("n=%d, target=%ld\n", n, target);
    int64_t base = 0;
    int pos = std::upper_bound(s, s + n + 1, target + base) - s;
    int regionNum = 1;

    while (pos != n + 1) {
        // assert(regionNum < 20);
        // printf("pos=%d, s[pos-1]=%ld, regionNum=%d\n", pos, s[pos-1], regionNum);
        base = s[pos - 1];
        pos = std::upper_bound(s + pos, s + n + 1, target + base) - s;
        regionNum++;
    }
    
    return regionNum;
}

int
main()
{
    int n, m;
    int64_t max, sum, left, right, mid;
    std::cin >> n >> m;

    max = -1;
    for (int i = 1; i <= n; i++) {
        std::cin >> s[i];
        max = std::max(max, s[i]);
        s[i] = s[i-1] + s[i];
    }

    sum = s[n];
    
    left = max;
    right = sum + 1;
    
    while (left < right) {
        mid = left + (right - left)/2;
        if (divide(n, mid) <= m) {
            right = mid;
        } else {
            left = mid + 1;
        }
        // printf("left=%ld, mid=%ld, right=%ld\n", left, mid, right);
    }

    std::cout << left << std::endl;

    return 0;
}