#include <iostream>
#include <limits>

class Solution
{
public:
  int myAtoi(const std::string &s)
  {
    auto it = s.begin();
    while (it != s.end() && *it == ' ') {
      ++it;
    }

    int sign = 1;
    if (*it == '-') {
      sign = -1;
      ++it;
    } else if (*it == '+') {
      ++it;
    }

    static_assert(sizeof(long long) == 8, "long long should be 8 bytes");
    long long num = 0;
    while (it != s.end() && std::isdigit(*it) != 0 && num < 0xff'ff'ff'ff) {
      num = num * 10 + *it - '0';
      ++it;
    }

    if (sign < 0) {
      num = ~num + 1;
    }

    if (num < std::numeric_limits<int>::min()) return std::numeric_limits<int>::min();
    if (num > std::numeric_limits<int>::max()) return std::numeric_limits<int>::max();
    
    return num;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout << Solution().myAtoi("+1") << '\n';
  std::cout << Solution().myAtoi("-1") << '\n';
  std::cout << Solution().myAtoi(" 1 ") << '\n';

  std::cout << Solution().myAtoi("+123") << '\n';
  std::cout << Solution().myAtoi("-123") << '\n';
  std::cout << Solution().myAtoi(" 123 ") << '\n';

  std::cout << Solution().myAtoi(" 12320000000000000000000 ") << '\n';

  return 0;
}