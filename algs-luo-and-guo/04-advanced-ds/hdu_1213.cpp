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
  int test_num;
  int n, m;
  int a, b;

  std::cin >> test_num;
  for (int test_i = 0; test_i < test_num; test_i++) {
    std::cin >> n >> m;
    DisjointSets ds(n + 1);
    for (int i = 0; i < m; i++) {
      std::cin >> a >> b;
      ds.union_set(a, b);
    }
    std::cout << ds.count_sets(1, n + 1) << std::endl;
  }
  return 0;
}