#include <bits/stdc++.h>

#define MAXN 2000
int n;
int c1, c2, c3;
int a[MAXN], b[MAXN];
int mina, minb;

static bool
isEqual(int ai, int bi)
{
    return (c1*(ai - mina) + c2*(bi - minb)) <= c3;
}

int
main()
{
    std::cin >> n;
    std::cin >> c1 >> c2 >> c3;
    mina = minb = INT32_MAX;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i] >> b[i];
        mina = std::min(mina, a[i]);
        minb = std::min(minb, b[i]);
    }
}