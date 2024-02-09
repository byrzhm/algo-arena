#include <bits/stdc++.h>

class Solution
{
public:
  bool isValid(const std::string &s)
  {
    std::stack<char> stack;
    for (auto c : s) {
      switch (c) {
        case '(':
        case '[':
        case '{':
          stack.push(c);
          break;
        case ')':
        {
          if (!stack.empty() && stack.top() == '(') {
            stack.pop();
          } else {
            return false;
          }
        } break;
        case ']':
        {
          if (!stack.empty() && stack.top() == '[') {
            stack.pop();
          } else {
            return false;
          }
        } break;
        case '}':
        {
          if (!stack.empty() && stack.top() == '{') {
            stack.pop();
          } else {
            return false;
          }
        } break;
        default:
          break;
      }
    }
    return stack.empty();
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s = "())";
  std::cout << (Solution().isValid(s) ? "true" : "false") << std::endl;
  return 0;
}