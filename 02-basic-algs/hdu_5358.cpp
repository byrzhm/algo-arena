#include <bits/stdc++.h>

const int MAXLOG = 33;

int64_t sumto[100005];

int
main()
{
    int testNum;
    int i, l, r, k, n;
    int64_t s, sum, min, max, len;
    std::cin >> testNum;

    while ((testNum--) != 0) {
        std::cin >> n;
        for (i = 1; i <= n; i++) {
            std::cin >> sumto[i];
            sumto[i] = sumto[i] + sumto[i-1];
        }

        sum = 0;
        min = 0; max = 1;
        for (k = 1; k <= MAXLOG + 1; k++) {
            s = 0;
            l = r = 1;
            // 左端点为 i 
            // 右端点可取的区间为 [l, r)
            for (i = 1; i <= n; i++) {
                l = std::max(i, l);
                while (l <= n && sumto[l] - sumto[i-1] < min)
                    l++;
                r = std::max(r, l);
                while (r <= n && sumto[r] - sumto[i-1] <= max
                              && sumto[r] - sumto[i-1] >= min)
                    r++;
                len = r - l;
                s += len * i + len * (l + r - 1) / 2;
                if (r != l)
                    printf("i=%d, l=%d, r=%d, k=%d\n", i, l, r, k);
            }
            min = max + 1;
            max = (min << 1) - 1;
            sum += s * k;
        }

        std::cout << sum << std::endl;
    }
    return 0;
}