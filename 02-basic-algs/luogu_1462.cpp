#include <bits/stdc++.h>

constexpr auto MAX = 10001;
constexpr int64_t INF = INT32_MAX;

struct Edge
{
    // int from;
    int to;
    int64_t weight;
    Edge(int to = 0, int64_t weight = INF) :
        to(to), weight(weight) {}
};

bool operator>(const Edge& l, const Edge& r) {
    return l.weight > r.weight;
}

int ver_wghts[MAX];
std::vector<Edge> graph[MAX];

int64_t
dijkstra(int n, int src, int dst, std::vector<int>& path)
{
    std::vector<bool> vis(n + 1, false);
    std::vector<int> trace(n + 1);
    std::vector<int64_t> dist(n + 1, INF);
    dist[src] = 0;

    /// first is weight, second is dest
    std::priority_queue<Edge, 
        std::vector<Edge>, 
        std::greater<Edge>> q;

    for (int i = 1; i <= n; i++)
        q.push({i, dist[i]});
    
    
    while (!q.empty()) {
        auto e = q.top();
        q.pop();

        // printf("pop: e.to=%d, e.weight=%ld\n", e.to, e.weight);

        if (vis[e.to]) continue;
        vis[e.to] = true;
        
        for (auto& d : graph[e.to]) {
            // printf("d.to=%d\n", d.to);
            // printf("dist[d.to]=%ld, e.weight=%ld, d.weight=%ld\n", 
                // dist[d.to], e.weight, d.weight);
            if (dist[d.to] > e.weight + d.weight) {
                dist[d.to] = e.weight + d.weight;
                trace[d.to] = e.to;
                q.push({d.to, dist[d.to]});
            }
        }
    }

    if (dist[dst] != INF) {
        int v = dst;
        while (v != src) {
            path.push_back(v);
            v = trace[v];
        }
        path.push_back(src);
    }

    // printf("dist[dst]=%ld\n", dist[dst]);
    return dist[dst];
}

static inline int
deleteMaxVertex(int n, int src, int dst, const std::vector<int>& path)
{
    int max = path[0], del;
    for (int i = 1; i < path.size(); i++)
        if (ver_wghts[max] < ver_wghts[path[i]])
            max = path[i];

    del = (max == dst ? src : max);

    // delete max vertex from graph
    for (auto& e : graph[del])
        e.weight = INF;
    // printf("max=%d, ver_wghts[max]=%d\n", max, ver_wghts[max]);

    return ver_wghts[max];
}

int
main()
{
    /// n = #vertices
    /// m = #edges
    /// b = #max path length
    int n, m, b;
    std::cin >> n >> m >> b;

    for (int i = 1; i <= n; i++)
        std::cin >> ver_wghts[i];

    for (int i = 0; i < m; i++) {
        int v1, v2, w;
        std::cin >> v1 >> v2 >> w;
        graph[v1].emplace_back(v2, w);
        graph[v2].emplace_back(v1, w);
    }

    int minMax = INF;
    int64_t length = 0;
    while (length <= b) {
        std::vector<int> path;
        if ((length = dijkstra(n, 1, n, path)) > b) continue;
        minMax = std::min(deleteMaxVertex(n, 1, n, path), minMax);
        // printf("minMax=%d\n", minMax);
    }
    
    if (minMax != INF)
        std::cout << minMax << std::endl;
    else
        std::cout << "AFK" << std::endl;

    return 0;
}
