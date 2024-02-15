// Monotonic Queues
#include <bits/stdc++.h>

constexpr auto MAX = 1000005;

std::deque<int> dq;
int a[MAX];

int
main()
{
    int n, k, x;
    int i;

    if (scanf("%d %d", &n, &k) != 2) {
        exit(-1);
    }

    for (i = 0; i < n; i++)
        if (scanf("%d", &a[i]) != 1)
            exit(-1);

    for (i = 0; i < n; i++) {
        while (!dq.empty() && a[dq.back()] > a[i])
            dq.pop_back();
        dq.push_back(i);

        if (i >= k - 1) {
            if (dq.front() == i - k) dq.pop_front();
            printf((i == n - 1 ? "%d\n" : "%d "), a[dq.front()]);
        }
    }

    while (!dq.empty())
        dq.pop_back();
    
    for (i = 0; i < n; i++) {
        while (!dq.empty() && a[dq.back()] < a[i])
            dq.pop_back();
        dq.push_back(i);

        if (i >= k - 1) {
            if (dq.front() == i - k) dq.pop_front();
            printf((i == n - 1 ? "%d\n" : "%d "), a[dq.front()]);
        }
    }
    exit(0);
}