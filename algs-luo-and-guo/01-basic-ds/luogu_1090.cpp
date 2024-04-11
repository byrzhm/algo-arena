#include <bits/stdc++.h>

int
main()
{
    int n, t, ans;
    std::priority_queue<int, std::vector<int>, std::greater<>> q;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> t;
        q.push(t);
    }

    ans = 0;
    while (q.size() > 1) {
        int t1 = q.top(); q.pop();
        int t2 = q.top(); q.pop();
        int sum = t1 + t2;
        ans += sum;
        q.push(sum);
    }
    std::cout << ans << std::endl;

    return 0;
}