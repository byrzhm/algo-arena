/**
 * topological sort
 * 按字典序输出所有的拓扑排序
 */
#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>

int n;
int a[25];
int topo[25];
int graph[30][30];
int indegree[30];
bool vis[30];

void backtrack(int z, int count)
{
  topo[count] = z;

  if (count == n - 1) {
    for (int i = 0; i < n; ++i)
      std::cout << static_cast<char>(topo[i] + 'a');
    std::cout << '\n';
    return;
  }

  vis[z] = true;

  for (int i = 0; i < n; ++i)
    if (!vis[a[i]] && (graph[z][a[i]] != 0))
      --indegree[a[i]];

  for (int i = 0; i < n; ++i)
    if ((indegree[a[i]] == 0) && !vis[a[i]])
      backtrack(a[i], count + 1);

  for (int i = 0; i < n; ++i)
    if (!vis[a[i]] && (graph[z][a[i]] != 0))
      ++indegree[a[i]];

  vis[z] = false;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string buf;

  while (std::getline(std::cin, buf)) {
    std::memset(graph, 0, sizeof(graph));
    std::memset(vis, 0, sizeof(vis));
    std::memset(indegree, 0, sizeof(indegree));

    n = 0;
    for (auto c : buf)
      if (std::isalpha(c) != 0)
        a[n++] = c - 'a';

    std::sort(a, a + n);

    std::getline(std::cin, buf);

    // 根据输入创建 Diagraph
    bool first = true;
    int u, v;
    for (auto c : buf) {
      if (first && (std::isalpha(c) != 0)) {
        first = false;
        u     = c - 'a';
        continue;
      }
      if (!first && (std::isalpha(c) != 0)) {
        first       = true;
        v           = c - 'a';
        graph[u][v] = 1;
        ++indegree[v];
        continue;
      }
    }

    for (int i = 0; i < n; ++i)
      if (indegree[a[i]] == 0)
        backtrack(a[i], 0);
    std::cout << '\n';
  }

  return 0;
}