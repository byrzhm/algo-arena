#include <bits/stdc++.h>

std::deque<int> dq;
int s[2000000];

int
main()
{
    int n, winsz, cnt;
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> s[i];
    memmove(&s[n], &s[0], sizeof(int) * (n-1));
    for (int i = 1; i < 2*n - 1; i++)
        s[i] = s[i-1] + s[i];

    cnt = 0;
    winsz = n;
    for (int i = 0; i < 2*n - 1; i++) {
        while (!dq.empty() && dq.front() <= i - winsz)
            dq.pop_front();
        if ((i > n-1 && s[dq.front()] - s[i-n] >= 0)
            || (i == n-1 && s[dq.front()] >= 0)) {
                cnt++;
        }
        while (!dq.empty() && s[dq.back()] > s[i])
            dq.pop_back();
        dq.push_back(i);
    }
    
    std::cout << cnt << std::endl;
    exit(0);
}