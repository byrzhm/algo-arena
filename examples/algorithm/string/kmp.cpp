#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

class KMP
{
public:
  KMP() = delete;

  explicit KMP(std::string _pat)
    : pat(std::move(_pat))
  {
    int M    = pat.size();
    auto set = alphabetSet(pat);
    for (auto c : set)
      dfa[c] = std::vector<int>(M);
    dfa[pat[0]][0] = 1;

    for (int X = 0, j = 1; j < M; j++) {
      for (auto c : set)
        dfa[c][j] = dfa[c][X];          // copy mismatch cases
      dfa[pat[j]][j] = j + 1;           // set match case

      X              = dfa[pat[j]][X];  // update restart state
    }
  }

  std::unordered_set<char> alphabetSet(const std::string &str)
  {
    std::unordered_set<char> set;
    for (auto c : str) {
      set.insert(c);
    }
    return set;
  }

  int search(const std::string &txt) const
  {
    int M = pat.size();
    int N = txt.size();
    int i, j;
    for (i = 0, j = 0; i < N && j < M; ++i) {
      j = dfa.at(txt[i])[j];
    }
    if (j == M)
      return i - M;
    return N;
  }

private:
  std::unordered_map<char, std::vector<int>> dfa;
  std::string pat;
};

int main()
{
  std::string pattern = "AAAAAAB";
  std::string text    = "AAAAAAAAAAAAAAAAAAAAAAB";
  KMP kmp(pattern);
  int idx = kmp.search(text);
  std::cout << text << '\n';

  for (int i = 0; i < idx; ++i)
    std::cout << ' ';
  std::cout << '*' << '\n';

  for (int i = 0; i < idx; ++i)
    std::cout << ' ';
  std::cout << pattern << '\n';
}
