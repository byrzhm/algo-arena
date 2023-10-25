#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> s;
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