#include <bits/stdc++.h>

std::deque<int> dq;
int s[500005];

// s[i] = a[0] + a[1] + ... + a[i]
// for i > j
// s[i] - s[j] = a[j+1] + a[j+2] + ... + a[i]

int
main()
{
    int n, m;
    int maxsum;
    std::cin >> n >> m;

    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
        if (i > 0)  s[i] = s[i-1] + s[i];
    }

    maxsum = s[0];
    dq.push_back(0);
    for (int i = 1; i < n; i++) {
        while (!dq.empty() && dq.front() < i - m)
            dq.pop_front();
        
        if (i < m)
            // maxsum = max{s[i], s[i] - s[dq.front()], maxsum}
            maxsum = std::max(s[i] - s[dq.front()], std::max(s[i], maxsum));
        else
            // maxsum = max{s[i] - s[dq.front()], maxsum}
            maxsum = std::max(s[i] - s[dq.front()], maxsum);

        while (!dq.empty() && s[dq.back()] > s[i])
            dq.pop_back();
        dq.push_back(i);
    }
    std::cout << maxsum << std::endl;
    exit(0);
}