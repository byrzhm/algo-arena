#include <bits/stdc++.h>
#include <boost/pending/disjoint_sets.hpp>

struct Edge {
  int from, to, weight;
};

bool operator<(const Edge &l, const Edge &r) {
  return l.weight < r.weight;
}

struct Graph {
  int vernum;
  std::vector<Edge> edges;
};

std::vector<Edge> KruskalMST(Graph &g) {
  std::vector<Edge> mst_edges;
  std::vector<int> rank(g.vernum + 1, 0);
  std::vector<int> parent(g.vernum + 1);
  boost::disjoint_sets<int *, int *> ds(rank.data(), parent.data());

  // Initialize each element as a separate set with itself as the representative
  for (int i = 1; i <= g.vernum; ++i) {
    parent[i] = i;
  }

  std::sort(g.edges.begin(), g.edges.end());
  for (const auto & e : g.edges) {
    if (ds.find_set(e.from) != ds.find_set(e.to)) {
      mst_edges.push_back(e);
      ds.union_set(e.from, e.to);
    }
  }

  return mst_edges;
}

int main() {
  Graph g;
  g.vernum = 4;
  g.edges.push_back({1, 2, 2});
  // g.edges.push_back({2, 1, 2});
  g.edges.push_back({1, 3, 2});
  // g.edges.push_back({3, 1, 2});
  g.edges.push_back({1, 4, 3});
  // g.edges.push_back({4, 1, 3});
  g.edges.push_back({2, 3, 4});
  // g.edges.push_back({3, 2, 4});
  g.edges.push_back({3, 4, 3});
  // g.edges.push_back({4, 3, 3});

  auto mst_edges = KruskalMST(g);
  for (auto & e : mst_edges) {
    std::cout << e.from << " -> " << e.to << ": " << e.weight << "\n";
  }
  return 0;
}