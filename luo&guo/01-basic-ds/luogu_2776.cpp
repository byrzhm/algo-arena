// 二维队列
#include <bits/stdc++.h>

int
main()
{
    int n, m, opnum, t;
    std::string op;
    std::cin >> n >> m;

    std::vector<int> a(n);
    std::queue<int> q;
    std::vector<std::queue<int>> last(m);

    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    std::cin >> opnum;

    for (int i = 0; i < opnum; i++) {
        std::cin >> op;

        if (op == "push") {
            std::cin >> t;
            if (last[a[t]].empty())
                q.push(a[t]);                // 队列q          push 组号
            last[a[t]].push(t);              // 队列last[a[t]] push 元素

        } else {
            std::cout << last[q.front()].front() << std::endl;
            last[q.front()].pop();
            if (last[q.front()].empty())
                q.pop();
        }
    }

    return 0;
}
