#include <bits/stdc++.h>

class Solution {
public:
 int largestRectangleArea(std::vector<int> &heights) {
   std::deque<int> dq;
   int ans, i;
   int n = heights.size();
   std::vector<int> left(n), right(n, n);

   for (i = 0; i < n; i++) {
     while (!dq.empty() && heights[dq.back()] > heights[i]) {
       right[dq.back()] = i;
       dq.pop_back();
     }
     left[i] = (dq.empty() ? -1 : dq.back());
     dq.push_back(i);
   }

   ans = INT_MIN;
   for (i = 0; i < n; i++) ans = std::max(ans, (right[i] - left[i] - 1) * heights[i]);

   return ans;
 }
};