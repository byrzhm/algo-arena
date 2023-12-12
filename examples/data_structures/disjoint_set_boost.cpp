/**
 * boost/pending/disjoint_sets.hpp
 * https://github.com/blackberry/Boost/blob/fc90c3fde129c62565c023f091eddc4a7ed9902b/boost/pending/disjoint_sets.hpp
 * compile command: g++ file.cpp -lboost_system
 *                   -lboost_system sometimes it not necessary, because we only use boost template header files
 */

#include <bits/stdc++.h>
#include <boost/pending/disjoint_sets.hpp>

int main() {
  int size = 5;
  std::vector<int> rank(size, 0);
  std::vector<int> parent(size);
  boost::disjoint_sets<int *, int *> ds(rank.data(), parent.data());

  // Initialize each element as a separate set with itself as the representative
  for (int i = 0; i < size; ++i) {
    parent[i] = i;
  }

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