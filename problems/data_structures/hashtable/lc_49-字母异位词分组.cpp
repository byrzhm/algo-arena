#include <bits/stdc++.h>

class Solution {
 public:
  std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string> &strs) {
    std::vector<std::vector<std::string>> anagrams;

    // ! which hash function is faster ?

    // auto hasher = [](const std::string &str) {
    //   size_t key = 0;
    //   for (auto &v : str) {
    //     key = key * 26 + (v - 'a');
    //   }
    //   return key;
    // };

    // std::unordered_map<std::string, std::vector<std::string>, decltype(hasher)> hashtable(100, hasher);

    std::unordered_map<std::string, std::vector<std::string>> hashtable(100);
    for (auto &str : strs) {
      std::string sorted = str;
      std::sort(sorted.begin(), sorted.end());

      hashtable[sorted].emplace_back(str);
    }

    int i = 0;
    anagrams.resize(hashtable.size());
    for (auto &[key, value] : hashtable) {
      anagrams[i].swap(value);
      ++i;
    }

    return anagrams;
  }
};