// #include <bits/stdc++.h>
#include <iostream>
#include <vector>

void
subseq()
{
    int n, s, sum;
    int start, end, len;
    std::cin >> n >> s;
    std::vector<int> v(n);
    for (int i = 0; i < n; i++)
        std::cin >> v[i];

    len = 0;
    start = end = 0;
    sum = 0;
    while (end <= n) {
        if (sum < s && end < n)
            sum += v[end++];
        
        if (sum < s && end == n)
            break;

        if (sum >= s) {
            while (sum - v[start] >= s)
                sum -= v[start++];

            len = (len == 0 ? end - start :
                    std::min(len, end - start));

            sum -= v[start++];
        }
    }
    std::cout << len << std::endl;
}

int
main()
{
    int testNum;
    std::cin >> testNum;

    while (testNum--) 
        subseq();
    
    return 0;
}