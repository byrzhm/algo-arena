// huffman
#include <bits/stdc++.h>

int
main()
{
    int n, m, num, ans;
    std::string input;
    std::priority_queue<int, std::vector<int>, std::greater<>> q;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> m;
        while (std::getchar() != '\n')
            continue;
        std::getline(std::cin, input);
        std::sort(input.begin(), input.end());
        for (int j = 1; j <= input.size(); j++) {
            if (input[j] != input[j-1]) {   // input[input.size()] == '\0'
                q.push(num);
                num = 1;
            } else 
                num++;
        }

        if (q.size() == 1)
            ans = input.size();
        else {
            ans = 0;
            while (q.size() > 1) {
                int t1 = q.top(); q.pop();
                int t2 = q.top(); q.pop();
                q.push(t1 + t2);
                ans += t1 + t2;
            }
            q.pop();
        }
        std::cout << (m >= ans ? "yes\n" : "no\n");
    }
}