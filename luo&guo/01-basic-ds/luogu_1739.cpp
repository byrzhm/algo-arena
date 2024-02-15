#include <bits/stdc++.h>

int
main()
{
    std::stack<char> s;
    char c;

    while ((c = getchar()) != '@') {
        if (c == '(')
            s.push(c);
        else if (c == ')' && !s.empty())
            s.pop();
        else if (c == ')' && s.empty()) {
            s.push('$');
            break;
        } else
            continue;
    }
    if (s.empty())
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;

    exit(0);
}