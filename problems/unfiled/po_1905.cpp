#include <iostream>
#include <cmath>
#include <cstdio>

#define eps 1e-5

double l0, l1, n, co;

int main()
{
    std::cin >> l0 >> n >> co;
    for (; l0 > 0; std::cin >> l0 >> n >> co) {
        l1 = (1 + n * co) * l0;
        double left, right;
        left = 0.0;
        right = l0;
        while (right - left > eps) {
            double mid = (left + right) / 2;
            double radius = (4 * mid * mid + l0 * l0) / (8 * mid);
            if (std::asin(l0/(2 * radius)) > l1 / (2 * radius))
                right = mid;
            else
                left = mid;
        }
        printf("%.3lf\n", left);
    }
}