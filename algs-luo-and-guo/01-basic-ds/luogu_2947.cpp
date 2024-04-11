#include <bits/stdc++.h>

int
main()
{
    int n;
    std::cin >> n;

    std::vector<int> heights(n), right(n, -1);
    for (int i = 0; i < n; i++)
        std::cin >> heights[i];

    std::stack<int> mono_stack;
    for (int i = 0; i < n; i++) {
        while (!mono_stack.empty() && heights[mono_stack.top()] < heights[i]) {
            right[mono_stack.top()] = i;
            mono_stack.pop();
        }
        mono_stack.push(i);
    }

    for (int val : right)
        std::cout << val+1 << std::endl;
    
    exit(0);
}