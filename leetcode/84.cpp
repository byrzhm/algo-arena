#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        deque<int> dq;
        int ans, i;
        int n = heights.size();
        vector<int> left(n), right(n, n);

        for (i = 0; i < n; i++) {
            while (!dq.empty() && heights[dq.back()] > heights[i]) {
                right[dq.back()] = i;
                dq.pop_back();
            }
            left[i] = (dq.empty() ? -1 : dq.back());
            dq.push_back(i);
        }

        ans = INT_MIN;
        for (i = 0; i < n; i++)
            ans = max(ans, (right[i] - left[i] - 1) * heights[i]);

        return ans;
    }
};