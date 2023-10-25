#include <bits/stdc++.h>

int
main()
{
    int n, t, mid;
    
    std::cin >> n;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minheap;
    std::priority_queue<int, std::vector<int>, std::less<int>> maxheap;
    for (int i = 0; i < n; i++) {
        std::cin >> t;

        if (minheap.size() == maxheap.size()) {
            if (maxheap.empty()) {
                mid = t;
                maxheap.push(t);
            } else {
                if (t < maxheap.top()) {
                    mid = maxheap.top();
                    maxheap.push(t);
                } else if (t > minheap.top()) {
                    mid = minheap.top();
                    minheap.push(t);
                } else {
                    mid = t;
                    maxheap.push(t);
                }
            }
            std::cout << mid << std::endl;
        } else if (minheap.size() > maxheap.size()) {
            if (t > minheap.top()) {
                maxheap.push(minheap.top());
                minheap.pop();
                minheap.push(t);
            } else
                maxheap.push(t);
        } else {
            if (t < maxheap.top()) {
                minheap.push(maxheap.top());
                maxheap.pop();
                maxheap.push(t);
            } else 
                minheap.push(t);
        }
    }

    exit(0);
}