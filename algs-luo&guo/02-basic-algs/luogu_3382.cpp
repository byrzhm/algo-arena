#include <bits/stdc++.h>

#define eps 1e-6

static inline double
func(const std::vector<double>& co, double x)
{
    int n = co.size();
    double ans = 0;
    for (int i = 0; i < n; i++)
        ans = x * ans + co[i];
    return ans;
}

int
main()
{
    int n;
    double l, r;
    std::cin >> n >> l >> r;
    std::vector<double> co(n + 1); // coefficient

    for (int i = 0; i <= n; i++)
        std::cin >> co[i];

    double left = l, right = r;
    // while (right - left > eps)
    for (int i = 0; i < 100; i++)
    {
        double mid = left + (right - left) / 2;
        double mid1 = mid - eps;
        double mid2 = mid + eps;
        // printf("%.5f, %.5f, %.5f\n", left, mid, right);
        if (func(co, mid1) > func(co, mid2)) {
            right = mid2;
        } else /* if (func(co, mid1) < func(co, mid2)) */ {
            left = mid1;
        }
    }

    printf("%.5f\n", left);
    return 0;
}