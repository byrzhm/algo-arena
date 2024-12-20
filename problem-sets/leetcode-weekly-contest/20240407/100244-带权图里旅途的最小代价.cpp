#include <iostream>
#include <queue>
#include <unordered_set>
#include <utility>
#include <vector>

using std::pair;
using std::queue;
using std::unordered_set;
using std::vector;

struct Edge
{
  int u, v, w;

  Edge(int u, int v, int w)
    : u(u)
    , v(v)
    , w(w)
  {}
};

class Graph
{
private:
  int V;
  vector<vector<int>> adj;
  vector<Edge> edges;
  vector<int> id;
  vector<int> weights;
  int count = 0;

public:
  explicit Graph(int V)
    : V(V)
  {
    adj.resize(V);
  }

  void addEdge(int u, int v, int w)
  {
    adj[u].push_back(v);
    adj[v].push_back(u);
    edges.emplace_back(u, v, w);
  }

  void findConnectedComponents()
  {
    vector<bool> marked(V);
    id.resize(V);
    for (int v = 0; v < V; ++v) {
      if (!marked[v]) {
        dfs(v, marked);
        ++count;
      }
    }
  }

  void calculateWeights()
  {
    weights.resize(count, -1);
    for (const Edge &edge : edges) {
      int i       = id[edge.u];
      weights[i] &= edge.w;
    }
  }

  int getWeight(int v)
  {
    return weights[id[v]];
  }

  bool connect(int u, int v)
  {
    return id[u] == id[v];
  }

private:
  void dfs(int v, vector<bool> &marked)
  {
    marked[v] = true;
    id[v]     = count;
    for (int u : adj[v])
      if (!marked[u])
        dfs(u, marked);
  }
};

class Solution
{
public:
  vector<int> minimumCost(int n, vector<vector<int>> &edges, vector<vector<int>> &query)
  {
    Graph g(n);
    for (const auto &edge : edges)
      g.addEdge(edge[0], edge[1], edge[2]);
    g.findConnectedComponents();
    g.calculateWeights();
    vector<int> ans;
    for (const auto &q : query) {
      int u = q[0];
      int v = q[1];
      if (u == v) {
        ans.push_back(0);
      } else if (g.connect(u, v)) {
        ans.push_back(g.getWeight(u));
      } else {
        ans.push_back(-1);
      }
    }
    return ans;
  }
};

namespace simplify {

class Solution
{
public:
  vector<int> minimumCost(int n, vector<vector<int>> &edges, vector<vector<int>> &query)
  {
    // build graph
    vector<vector<pair<int, int>>> adj(n);
    for (const auto &edge : edges) {
      int u = edge[0], v = edge[1], w = edge[2];
      adj[u].emplace_back(v, w);
      adj[v].emplace_back(u, w);
    }

    // find connected components
    vector<int> id(n, -1);
    vector<int> andWeights;

    int count = 0;
    for (int i = 0; i < n; ++i) {
      if (id[i] < 0) {
        andWeights.push_back(-1);

        queue<int> q;
        q.push(i);
        while (!q.empty()) {
          int u = q.front();
          q.pop();

          id[u] = count;

          for (const auto &[v, w] : adj[u]) {
            andWeights.back() &= w;
            if (id[v] < 0)
              q.push(v);
          }
        }

        ++count;
      }
    }

    vector<int> ans;
    for (const auto &q : query) {
      int s = q[0], t = q[1];
      if (s == t)
        ans.push_back(0);
      else if (id[s] == id[t])
        ans.push_back(andWeights[id[s]]);
      else
        ans.push_back(-1);
    }

    return ans;
  }
};

}  // namespace simplify

int main()
{
  int n = 3;
  vector<vector<int>> edges{
      {0, 2, 7},
      {0, 1, 15},
      {1, 2, 6},
      {1, 2, 1}
  };
  vector<vector<int>> query{
      {1, 2}
  };
  vector<int> ans = Solution().minimumCost(n, edges, query);
  for (int a : ans) {
    std::cout << a << " ";
  }
  std::cout << '\n';
}