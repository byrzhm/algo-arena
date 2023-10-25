#include <algorithm>
#include <bits/stdc++.h>
#include <list>
#include <unordered_map>
#include <utility>
using namespace std;

class LRUCache {
    unordered_map<int, int> node_store_;
    list<int> history_;
    int capacity_;
public:
    LRUCache(int capacity) : capacity_(capacity) {}
    
    int get(int key) {
        auto ptr = node_store_.find(key);
        if (ptr != node_store_.end()) {
            
        } else {

        }
    }
    
    void put(int key, int value) {

    }
};