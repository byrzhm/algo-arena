#include <bits/stdc++.h>

std::deque<int> dq;
int a[2000000];

int
main()
{
    int n, k;
    std::cin >> n >> k;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    for (int i = 0; i < n; i++) {
        while (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();
        while (!dq.empty() && a[dq.back()] < a[i])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1)
            printf("%d\n", a[dq.front()]);
    }
}