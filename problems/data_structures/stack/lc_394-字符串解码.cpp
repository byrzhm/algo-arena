#include <bits/stdc++.h>

class Solution
{
public:
  std::string decodeString(const std::string &s)
  {
    std::string decode;
    std::stack<char> stack;
    for (auto c : s) {
      if (c != ']') {
        stack.push(c);
      } else {
        std::string sub;
        while (!stack.empty() && stack.top() != '[') {
          sub.push_back(stack.top());
          stack.pop();
        }
        // std::reverse(sub.begin(), sub.end());

        stack.pop();  // 去除 '['

        std::string numStr;
        while (!stack.empty() && static_cast<bool>(std::isdigit(stack.top()))) {
          numStr.push_back(stack.top());
          stack.pop();
        }
        std::reverse(numStr.begin(), numStr.end());
        int num = std::stoi(numStr);

        for (int i = 0; i < num; ++i) {
          for (auto it = sub.rbegin(); it != sub.rend(); ++it) {
            stack.push(*it);
          }
        }
      }
    }

    while (!stack.empty()) {
      decode.push_back(stack.top());
      stack.pop();
    }
    std::reverse(decode.begin(), decode.end());
    return decode;
  }
};