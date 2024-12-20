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

int PrimMST(const Graph &g, int root) {
  int len_sum = 0;
  int edge_count = 0;
  int vernum = g.vernum - 1;
  std::vector<bool> in_mst(vernum + 1, false);
  std::priority_queue<Edge, std::vector<Edge>, std::greater<>> pq;
  
  in_mst[root] = true;

  for (const auto & e : g.adj[root]) {
    pq.push(e);
  }

  while (!pq.empty()) {
    auto edge = pq.top();
    pq.pop();

    int next = edge.to;
    if (!in_mst[next]) {
      // Include the current edge in the MST
      // std::cout << "Edge: " << edge.from << " - " << edge.to << " | Weight: " << edge.weight << std::endl;
      len_sum += edge.weight;
      ++edge_count;

      in_mst[next] = true;

      for (const auto &e : g.adj[next]) {
        if (!in_mst[e.to]) {
          pq.push(e);
        }
      }
    }
  }
  if (edge_count != vernum - 1) {
    std::cout << "orz" << std::endl;
    exit(0);
  }
  return len_sum;
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
  std::cout << PrimMST(g, 1) << std::endl;

  return 0;
}