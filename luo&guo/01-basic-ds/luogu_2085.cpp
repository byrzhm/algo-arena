#include <bits/stdc++.h>

int
main()
{
    int n, m;
    std::cin >> n >> m;

    std::stack<int> s;
    std::priority_queue<int> maxheap;
    std::vector<int> a(n), b(n), c(n);

    for (int i = 0; i < n; i++)
        std::cin >> a[i] >> b[i] >> c[i];
    
    for (int x = 1; x <= m; x++) {
        for (int i = 0; i < n; i++) {
            int acc = a[i]*x*x + b[i]*x + c[i];
            if (maxheap.size() < m + 1)
                maxheap.push(acc);
            else if (maxheap.top() > acc) {
                maxheap.pop();
                maxheap.push(acc);
            }
        }
    }

    if (maxheap.size() == m + 1)
        maxheap.pop();
    while (!maxheap.empty()) {
        s.push(maxheap.top());
        maxheap.pop();
    }

    while (!s.empty()) {
        std::cout << s.top();
        s.pop();
        if (!s.empty())
            std::cout << ' ';
    }
    std::cout << std::endl;

    exit(0);
}