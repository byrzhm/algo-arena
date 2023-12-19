#include <algorithm>
#include <bits/stdc++.h>
#include <list>
#include <unordered_map>
#include <utility>

class LRUCache {
  std::unordered_map<int, int> node_store_;
  std::list<int> history_;
  int capacity_;

 public:
  explicit LRUCache(int capacity) : capacity_(capacity) {}

  int get(int key) {
    auto ptr = node_store_.find(key);
    // if (ptr != node_store_.end()) {

    // } else {

    // }
        return {};
    }
    
    void put(int key, int value) {

    }
};