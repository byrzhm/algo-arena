#include <iostream>

#define MAXN 100000
int a[MAXN];
int n, m;

bool
checkmid(long long x)
{
    long long sum = 0;
    int count = 1;
    for (int i = 0; i < n; i++) {
        if (sum + a[i] > x) {
            count++;
            sum = 0;
        }
        sum += a[i];
    }

    return count <= m;
}

int
main()
{
    long long sum = 0;
    int max = -1;
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        max = std::max(a[i], max);
        sum += a[i];
    }

    long long left = max;
    long long right = sum;

    while (left < right) {
        long long mid = (left + right) >> 1;
        if (checkmid(mid)) 
            right = mid;
        else
            left = mid + 1;
    }

    std::cout << left << std::endl;
    return 0;
}