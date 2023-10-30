#include <bits/stdc++.h>

std::string s;

static inline void
print(int pos, int n)
{
    int i;
    char c = s[pos];
    for (i = 1; i < n; i++)
        if (c != s[pos + i])
            break;
    if (i == n)
        std::cout << (c == '0' ? 'B' : 'I');
    else
        std::cout << 'F';
}

void
postorder(int pos, int n)
{
    if (n > 0) {
        postorder(pos, n/2);
        postorder(pos + n/2, n/2);
        print(pos, n);
    }
}

int
main()
{
    int n;

    std::cin >> n;
    std::cin >> s;

    postorder(0, static_cast<int>(pow(2, n)));
    std::cout << std::endl;
}