/**
 *  208. 实现 Trie (前缀树)
 *  2416. 字符串的前缀分数和 1725
 *  336. 回文对
 *  745. 前缀和后缀搜索
 *  3045. 统计前后缀下标对 II 2328
 *  527. 单词缩写（会员题）
 *  1804. 实现 Trie （前缀树） II（会员题）
 */

#include <algorithm>
#include <limits>
#include <memory>
#include <string>
#include <vector>
using std::min;
using std::numeric_limits;
using std::reverse;
using std::string;
using std::unique_ptr;
using std::vector;

class Trie
{
public:
  Trie()
    : children_(vector<unique_ptr<Trie>>(26))
  {}

  void insert(const string &word, int val)
  {
    auto ptr = this;
    for (char c : word) {
      c         = c - 'a';
      ptr->val_ = min(ptr->val_, val);
      if (ptr->children_[c] == nullptr)
        ptr->children_[c] = std::make_unique<Trie>();
      ptr = ptr->children_[c].get();
    }
    ptr->val_ = min(ptr->val_, val);
  }

  int search(const string &word)
  {
    if (word.empty()) {
      return val_;
    }

    auto ptr = this;
    for (char c : word) {
      c = c - 'a';
      if (ptr->children_[c] == nullptr)
        return ptr->val_;
      ptr = ptr->children_[c].get();
    }

    return ptr->val_;
  }

private:
  int val_{numeric_limits<int>::max()};
  vector<unique_ptr<Trie>> children_;
};

class Solution
{
public:
  vector<int> stringIndices(vector<string> &wc, vector<string> &wq)
  {
    Trie trie;
    for (int i = 0; i < wc.size(); ++i) {
      auto &cstr = wc[i];
      reverse(cstr.begin(), cstr.end());
      trie.insert(cstr, cstr.size() * 100000 + i);
      // 0 <= i < wordsContainer.length <= 10000
    }

    vector<int> ans(wq.size());
    for (int i = 0; i < wq.size(); ++i) {
      auto &qstr = wq[i];
      reverse(qstr.begin(), qstr.end());
      int size = qstr.size();
      ans[i]   = trie.search(qstr) % 100000;
    }

    return ans;
  }
};