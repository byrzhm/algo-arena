#include <bits/stdc++.h>

std::deque<int> dq;
int a[2000005];

int
main()
{
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        exit(-1);
    }
    for (int i = 0; i < n; i++)
        if (scanf("%d", &a[i]) != 1)
            exit(-1);

    printf("0\n");
    dq.push_back(0);

    for (int i = 1; i < n; i++) {
        while (!dq.empty() && dq.front() < i-m)
            dq.pop_front();

        printf("%d\n", a[dq.front()]);

        while (!dq.empty() && a[dq.back()] > a[i])
            dq.pop_back();
        dq.push_back(i);
    }
    exit(0);
}