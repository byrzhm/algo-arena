#include <bits/stdc++.h>

/**
 * @brief A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and retrieve
 * keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and
 * spellchecker.
 */

namespace recursive {

class Trie {
 public:
  Trie() : children(std::vector<std::unique_ptr<Trie>>(26)) {}

  void insert(const std::string &word, int level = 0) {
    if (level == word.size()) {
      isLeaf = true;
      return;
    }

    int c = word[level] - 'a';
    if (children[c] == nullptr) {
      children[c] = std::make_unique<Trie>();
    }

    children[c]->insert(word, level + 1);
  }

  bool search(const std::string &word, int level = 0) const {
    if (level == word.size()) return isLeaf;

    int c = word[level] - 'a';
    if (children[c] == nullptr) return false;

    return children[c]->search(word, level + 1);
  }

  bool startsWith(const std::string &prefix, int level = 0) const {
    if (prefix.size() == level) return true;

    int c = prefix[level] - 'a';
    if (children[c] == nullptr) return false;

    return children[c]->startsWith(prefix, level + 1);
  }

 private:
  bool isLeaf{false};
  std::vector<std::unique_ptr<Trie>> children;  // use raw pointer will be faster?
};

}  // namespace recursive

namespace iterative {

class Trie {
 public:
  Trie() : children(std::vector<std::unique_ptr<Trie>>(26)) {}

  void insert(const std::string &word) {
    if (word.empty()) {
      isLeaf = true;
      return;
    }

    auto ptr = this;
    for (char c : word) {
      c = c - 'a';
      if (ptr->children[c] == nullptr) ptr->children[c] = std::make_unique<Trie>();
      ptr = ptr->children[c].get();
    }
    ptr->isLeaf = true;
  }

  bool search(const std::string &word) const {
    if (word.empty()) return isLeaf;

    auto ptr = this;
    for (char c : word) {
      c = c - 'a';
      if (ptr->children[c] == nullptr) return false;
      ptr = ptr->children[c].get();
    }

    return ptr->isLeaf;
  }

  bool startsWith(const std::string &prefix) const {
    if (prefix.empty()) return true;

    auto ptr = this;
    for (char c : prefix) {
      c = c - 'a';
      if (ptr->children[c] == nullptr) return false;
      ptr = ptr->children[c].get();
    }

    return true;
  }

 private:
  bool isLeaf{false};
  std::vector<std::unique_ptr<Trie>> children;  // use raw pointer will be faster?
};

}  // namespace iterative

int main() {
  auto *obj = new iterative::Trie();
  obj->insert("apple");
  std::cout << obj->search("apple") << '\n';
  std::cout << obj->search("app") << '\n';
  std::cout << obj->startsWith("app") << '\n';
  obj->insert("app");
  std::cout << obj->search("app") << '\n';
  delete obj;
}