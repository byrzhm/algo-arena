// #include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <cmath>

// constexpr auto MAXN = 10000;
// constexpr auto eps = 1e-5;
#define MAXN 10000
#define eps 1e-5
const double PI = std::acos(-1.0);
double area[MAXN];

bool
piecheck(int n, int m, double target)
{
    int num = 0;
    for (int i = 0; i < n; i++)
        num += static_cast<int>(area[i]/target);
    
    return num >= m;
}

int
main()
{
    int testNum;
    int n, m;
    std::cin >> testNum;

    while ((testNum--) != 0) {
        double left, right;
        double max = -1;
        std::cin >> n >> m;
        m++;
        for (int i = 0; i < n; i++) {
            int radius;
            std::cin >> radius;
            area[i] = PI * radius * radius;
            max = std::max(area[i], max);
        }

        left = 0;
        right = max;

        while (right - left > eps) {
            double mid = left + (right - left) / 2;
            if (piecheck(n, m, mid)) {
                left = mid;
            } else {
                right = mid;
            }
        }

        std::cout << std::fixed << std::setprecision(4) << left << std::endl;

    }

    return 0;
}