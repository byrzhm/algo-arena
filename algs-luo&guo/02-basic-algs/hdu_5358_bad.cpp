#include <bits/stdc++.h>

// const int MAXLOG = int(log2(1e5*1e5));
const int MAXLOG = 33;

int64_t sumto[100005];

void
printSumto(int n)
{
    for (int i = 0; i <= n; i++)
        std::cout << sumto[i] << ' ';
    std::cout << std::endl;
    std::cout << std::endl;
}

int
main()
{
    int testNum;
    int i, j, k, n;
    int64_t s, sum;
    std::cin >> testNum;

    while ((testNum--) != 0) {
        std::cin >> n;
        for (i = 1; i <= n; i++) {
            std::cin >> sumto[i];
            sumto[i] = sumto[i] + sumto[i-1];
        }
        printSumto(n);

        sum = 0;
        for (k = 1; k <= MAXLOG + 1; k++) {
            int64_t min = 1L << (k - 1);
            int64_t max = (1L << k) - 1;
            if (k == 1) min = 0;

            i = 0; j = 1;
            while (j <= n) {
                s = sumto[j] - sumto[i];

                if (s <= max && s >= min) {
                    sum += (i + 1 + j) * k;
                    printf("i=%d, j=%d, s=%ld, sum=%ld, k=%d\n", i, j, s, sum, k);
                    i++;
                }

                if (s > max) i++;
                if (s < min) j++;
                if (i == j) j++;
            }

        }

        std::cout << sum << std::endl;
    }
    return 0;
}