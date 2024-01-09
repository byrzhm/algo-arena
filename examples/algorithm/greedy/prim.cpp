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

void PrimMST(const Graph &g, int root) {
  std::vector<bool> in_mst(g.vernum + 1, false);
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
      std::cout << "Edge: " << edge.from << " - " << edge.to << " | Weight: " << edge.weight << std::endl;

      in_mst[next] = true;

      for (const auto &e : g.adj[next]) {
        if (!in_mst[e.to]) {
          pq.push(e);
        }
      }
    }
  }
}

int main() {
    Graph g(4 + 1);

    g.AddEdge(1, 2, 2);
    g.AddEdge(1, 3, 2);
    g.AddEdge(1, 4, 3);
    g.AddEdge(2, 3, 4);
    g.AddEdge(3, 4, 3);

    std::cout << "Minimum Spanning Tree (Prim's Algorithm):" << std::endl;
    PrimMST(g, 1);

    return 0;
}