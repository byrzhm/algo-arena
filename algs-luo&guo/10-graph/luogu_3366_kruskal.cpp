#include <bits/stdc++.h>

struct Edge {
  int from, to, weight;
};

bool operator<(const Edge &l, const Edge &r) {
  return l.weight < r.weight;
}

bool operator>(const Edge &l, const Edge &r) {
  return l.weight > r.weight;
}

struct Graph {
  int vernum;
  std::vector<std::vector<Edge>> adj;

  explicit Graph(int size) : vernum(size) {
    adj.resize(size);
  }

  void AddEdge(int from, int to, int weight) {
    adj[from].push_back({from, to, weight});
    adj[to].push_back({to, from, weight});
  }
};

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

std::vector<Edge> KruskalMST(const Graph &g) {
  std::vector<Edge> mst_edges;
  std::vector<Edge> total_edges;
  DisjointSets ds(g.vernum);

  for (int i = 1; i <= g.vernum - 1; ++i) {
    for (const auto &e : g.adj[i]) {
      total_edges.push_back(e);
    }
  }

  std::sort(total_edges.begin(), total_edges.end());
  for (const auto & e : total_edges) {
    if (ds.find_set(e.from) != ds.find_set(e.to)) {
      mst_edges.push_back(e);
      ds.union_set(e.from, e.to);
    }
  }

  return mst_edges;
}

int main() {
  int vernum, edgenum;
  std::cin >> vernum >> edgenum;

  Graph g(vernum + 1);
  
  for (int i = 0; i < edgenum; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    g.AddEdge(u, v, w);
  }

  int sum = 0;
  auto mst_edges = KruskalMST(g);
  if (mst_edges.size() != vernum - 1) {
    std::cout << "orz" << std::endl;
    return 0;
  }

  for (const auto &e : mst_edges) {
    sum += e.weight;
  }
  std::cout << sum << std::endl;

  return 0;
}