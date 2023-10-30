#include <bits/stdc++.h>

int a[1000000];

int
main()
{
    int testNum;
    std::cin >> testNum;

    while ((testNum--) != 0) {
        int n, l, r, max;
        std::cin >> n;
        std::unordered_map<int, int> hash;
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
            hash[a[i]] = 0;
        }

        max = 0;
        l = r = 0;
        while (r <= n) {
            while (r < n && (hash[a[r]] == 0)) {
                hash[a[r]] = 1;
                r++;
            }
            max = std::max(max, r - l);
            while (r < n && (hash[a[r]] != 0)) {
                hash[a[l]] = 0;
                l++;
            }
            hash[a[r]] = 1;
            r++;
        }
        std::cout << max << std::endl;
    }
    return 0;
}