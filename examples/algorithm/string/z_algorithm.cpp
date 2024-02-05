/**
 * https://www.youtube.com/watch?v=CpZh4eF8QBw
 * https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
 */
#include <iostream>
#include <string>
#include <vector>

/**
 * Z array
 * Z[k] = longest substring (length) starting at k which is also prefix of the string
 * Z[0]并不重要, 按照定义应该是字符串的总长
 *
 *       a   a   b   x   a   a   y   a   a   b
 *       0   1   2   3   4   5   6   7   8   9
 *  Z[]: -   1   0   0   2   1   0   3   1   0
 */

class ZAlgorithm
{
public:
  // prints all occurrences of pattern in text using Z algo
  void search(const std::string &text, const std::string &pattern)
  {
    // Create concatenated string "P$T"
    std::string concat = pattern + "$" + text;
    int l              = concat.length();

    // Construct Z array
    std::vector<int> z = getZarr(concat);

    // now looping through Z array for matching condition
    for (int i = 0; i < l; ++i)
    {
      // if zarr[i] (matched region) is equal to pattern
      // length we got the pattern
      if (z[i] == pattern.length())
        std::cout << "Pattern found at index "
                  << i - pattern.length() - 1 << std::endl;
    }
  }

private:
  std::vector<int> getZarr(const std::string &str)
  {
    int n = str.length();
    std::vector<int> z(n);
    z[0]      = n;  // z[0] doesn't matter
    int left  = 0;
    int right = 0;

    for (int i = 1; i < n; ++i) {
      if (i > right) {
        left = right = i;
        while (right < n && str[right - left] == str[right])
          ++right;
        z[i] = right - left;
        --right;
      } else {
        int k = i - left;
        if (z[k] < right - i + 1) {
          z[i] = z[k];
        } else {
          left = i;
          while (right < n && str[right - left] == str[right])
            ++right;
          z[i] = right - left;
          --right;
        }
      }
    }

    return z;
  }
};
// Driver program
int main()
{
  std::string text    = "GEEKS FOR GEEKS";
  std::string pattern = "GEEK";
  ZAlgorithm().search(text, pattern);
  return 0;
}