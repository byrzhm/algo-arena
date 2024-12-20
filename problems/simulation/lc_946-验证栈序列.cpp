#include <bits/stdc++.h>

class Solution {
public:
 bool validateStackSequences(std::vector<int> &pushed, std::vector<int> &popped) {
   std::stack<int> s;
   int size = pushed.size();
   int idx = 0;

   for (int i = 0; i < size; i++) {
     s.push(pushed[i]);
     while (!s.empty() && s.top() == popped[idx]) {
       s.pop();
       ++idx;
     }
   }
   return idx == size;
 }
};