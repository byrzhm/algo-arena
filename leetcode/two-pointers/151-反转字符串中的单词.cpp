#include <bits/stdc++.h>

class Solution {
public:
 std::string reverseWords(std::string s) {
   std::reverse(s.begin(), s.end());

   int n = s.size();
   int idx = 0;

   for (int start = 0; start < n; start++) {
     if (s[start] != ' ') {
       if (idx != 0) s[idx++] = ' ';

       int end = start;
       while (end < n && s[end] != ' ') s[idx++] = s[end++];

       std::reverse(s.begin() + idx - (end - start), s.begin() + idx);

       start = end;
     }
   }

   s.erase(s.begin() + idx, s.end());
   return std::move(s);

   // string ans;
   // stack<char> stack;
   // unique_ptr<string> word;
   // vector<unique_ptr<string>> words;
   // int n = s.size();
   // for (int i = n - 1; i >= 0; --i) {
   //     char c = s.at(i);
   //     if (stack.empty() && isspace(c))
   //         continue;
   //     if (!stack.empty() && isspace(c)) {
   //         word = make_unique<string>();
   //         while (!stack.empty()) {
   //             word->push_back(stack.top());
   //             stack.pop();
   //         }
   //         words.push_back(move(word));
   //         continue;
   //     }
   //     stack.push(c);
   // }

   // if (!stack.empty()) {
   //     word = make_unique<string>();
   //     while (!stack.empty()) {
   //         word->push_back(stack.top());
   //         stack.pop();
   //     }
   //     words.push_back(move(word));
   // }

   // int wordNum = words.size();
   // for (int i = 0; i < wordNum; i++) {
   //     ans += move(*words[i]);
   //     if (i != wordNum - 1) ans += ' ';
   // }

   // return move(ans);
 }
};