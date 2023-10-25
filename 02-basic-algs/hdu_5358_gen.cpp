#include <bits/stdc++.h>

constexpr auto MAX_N = 10;
constexpr auto MIN_N = 1;

constexpr auto MAX_A = 100;
constexpr auto MIN_A = 0;

uint64_t RandNum() {
    return    ((random() & 0xffff) << 48) 
            | ((random() & 0xffff) << 32)
            | ((random() & 0xffff) << 16)
            | ((random() & 0xffff));
}

int
main()
{
    int n;
    srandom(time(0));
    std::cout << 1 << std::endl;
    
    (n = static_cast<int>(RandNum() % (MAX_N - MIN_N + 1) + MIN_N));
    std::cout << n << std::endl;
    for (int i = 0; i < n; i++)
        std::cout << static_cast<int>(RandNum() % (MAX_A - MIN_A + 1) + MIN_A)
                  << (i == n-1 ? '\n' : ' ');
    exit(0);
}