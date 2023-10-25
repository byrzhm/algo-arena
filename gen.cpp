#include <bits/stdc++.h>

constexpr auto MAX = 1000000;
constexpr auto MIN = 1;

int RandNum() {
    return    ((random() & 0xffff) << 16)
            | ((random() & 0xffff));
}

int
main()
{
    int n, k;

    srandom(time(0));

    k = random() % (MAX - MIN + 1) + MIN;
    n = random() % (MAX - k + 1) + k;
    printf("%d %d\n", n, k);

    for (int i = 0; i < n; i++)
        printf((i == n - 1 ? "%d\n" : "%d "), RandNum());
}