#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;

class Solution
{
public:
  int maximumLengthSubstring(string s)
  {
    unordered_map<char, int> map;
    int i, j;
    int len = 2;
    for (i = 0, j = 0; i < s.size(); ++i) {
      while (map[s[i]] == 2) {
        --map[s[j++]];
      }
      ++map[s[i]];
      if (i - j + 1 > len) {
        len = i - j + 1;
      }
    }
    return len;
  }
};