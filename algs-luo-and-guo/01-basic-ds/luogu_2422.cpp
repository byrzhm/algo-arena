#include <bits/stdc++.h>

std::deque<int> dq;
int a[100001];
int left[100001], right[100001];
int64_t s[100001];

int
main()
{
    int i, n;
    int64_t ans;
    std::cin >> n;

    for (i = 1; i <= n; i++) {
        std::cin >> a[i];
        s[i] = a[i] + s[i-1];   // s[i] = a[1] + a[2] + ... + a[i]
        right[i] = n + 1;       // default right value
    }

    for (i = 1; i <= n; i++) {
        // maintain a monotonic stack
        while (!dq.empty() && a[dq.back()] > a[i]) {
            right[dq.back()] = i;
            dq.pop_back();
        }
        left[i] = (dq.empty() ? 0: dq.back());
        dq.push_back(i);
    }

    ans = -INT_MAX;
    for (i = 1; i <= n; i++)
        ans = std::max((s[right[i] - 1] - s[left[i]]) * a[i], ans);

    std::cout << ans << std::endl;
    exit(0);
}