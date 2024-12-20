#include <bits/stdc++.h>

class Solution
{
public:
  std::vector<int> dailyTemperatures(std::vector<int> &temperatures)
  {
    int n = temperatures.size();
    std::stack<int> monoStack;
    std::vector<int> dist(n, 0);

    for (int i = 0; i < n; ++i) {
      while (!monoStack.empty() && temperatures[i] > temperatures[monoStack.top()]) {
        dist[monoStack.top()] = i - monoStack.top();
        monoStack.pop();
      }
      monoStack.push(i);
    }

    return dist;
  }
};