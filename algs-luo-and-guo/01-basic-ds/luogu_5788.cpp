#include <bits/stdc++.h>

int 
main()
{
    int n;
    std::stack<int> s;

    std::cin >> n;
    std::vector<int> a(n), f(n, -1);
    
    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    for (int i = 0; i < n; i++) {
        while (!s.empty() && a[s.top()] < a[i]) {
            f[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }

    for (int i = 0; i < n; i++)
        std::cout << f[i] + 1 << (i == n - 1 ? '\n' : ' ');
    
    return 0;
}