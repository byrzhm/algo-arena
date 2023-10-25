#include <bits/stdc++.h>

constexpr auto eps = 1e-9;
constexpr auto MAX = 10004;
std::array<std::array<int, 3>, MAX> co;
int n;

auto func(double x) -> double
{
    double max = -1e16;
    for (int i = 0; i < n; i++) {
        double ans = 0.0;
        for (int j = 0; j < 3; j++)
            ans = ans * x + co[i][j];
        max = std::max(ans, max);
    }
    return max;
}

auto main() -> int
{
    int testNum;
    std::cin >> testNum;

    while (testNum--) {
        std::cin >> n;
        for (int i = 0; i < n; i++) // 二次函数可能退化为一次
            std::cin >> co[i][0] >> co[i][1] >> co[i][2];

        double left = 0.0;
        double right = 1000.0;

        while (right - left > eps) {
            double mid1 = left + (right - left) / 3;
            double mid2 = right - (right - left) / 3;

            // printf("left=%lf, mid1=%lf, mid2=%lf, right=%lf\n", 
            //     left, mid1, mid2, right);

            if (func(mid1) > func(mid2)) {
                left = mid1;
            } else {
                right = mid2;
            }
        }
        printf("%.4lf\n", func(left));
    }

    return 0;
}