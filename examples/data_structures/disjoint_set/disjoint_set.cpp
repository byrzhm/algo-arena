#include <bits/stdc++.h>

class DisjointSets {
public:
  explicit DisjointSets(int size) {
    parent.resize(size);
    rank.resize(size, 0);

    for (int i = 0; i < size; i++) {
      parent[i] = i;
    }
  }

  int find_set(int x) {
    // path compession
    int old = x;
    int ancestor = parent[x];
    while (ancestor != x) {
      x = ancestor;
      ancestor = parent[x];
    }
    x = parent[old];
    while (ancestor != x) {
      parent[old] = ancestor;
      old = x;
      x = parent[old];
    }
    return ancestor;
  }

  void link(int x, int y) {
    if (x == y)
      return;

    if (rank[x] > rank[y])
      parent[y] = x;
    else {
      parent[x] = y;
      if (rank[x] == rank[y])
        ++rank[y];
    }
  }

  void union_set(int x, int y) {
    link(find_set(x), find_set(y));
  }

  int count_sets(int first, int last) const {
    int count = 0;
    for (; first != last; ++first) {
      if (parent[first] == first)
        ++count;
    }
    return count;
  }
  
private:
  std::vector<int> parent;
  std::vector<int> rank;
};

int main() {
    // Example usage
    int size = 5;
    DisjointSets ds(size);

    ds.union_set(0, 1);
    ds.union_set(2, 3);
    ds.union_set(0, 4);

    // Check if 1 and 4 are in the same set
    if (ds.find_set(1) == ds.find_set(4)) {
        std::cout << "1 and 4 are in the same set." << std::endl;
    } else {
        std::cout << "1 and 4 are not in the same set." << std::endl;
    }

    return 0;
}