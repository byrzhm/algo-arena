#include <bits/stdc++.h>

/**
 * @brief There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an
 * array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to
 * take course ai.
 */
namespace slow {

class Solution {
 public:
  bool canFinish(int numCourses, std::vector<std::vector<int>> &prerequisites) {
    std::vector<std::unordered_set<int>> dependency_graph(numCourses);
    for (auto &preq : prerequisites) {
      dependency_graph[preq[0]].insert(preq[1]);
    }
    int count = 0;
    bool changed = true;
    std::vector<bool> visited(numCourses, false);
    while (changed) {
      changed = false;
      for (int i = 0; i < numCourses; i++) {
        if (dependency_graph[i].empty() && !visited[i]) {
          ++count;
          changed = true;
          visited[i] = true;
          for (int j = 0; j < numCourses; j++) {
            dependency_graph[j].erase(i);
          }
        }
      }
    }
    return count == numCourses;
  }
};

}  // namespace slow

namespace fast {

class Solution {
 public:
  bool canFinish(int numCourses, std::vector<std::vector<int>> &prerequisites) {
    std::vector<std::vector<int>> dependency_graph(numCourses);
    std::vector<int> indegree(numCourses, 0);
    for (auto &preq : prerequisites) {
      dependency_graph[preq[1]].emplace_back(preq[0]);  // 改变指向
      ++indegree[preq[0]];
    }
    std::queue<int> queue;
    for (int i = 0; i < numCourses; ++i)
      if (indegree[i] == 0) queue.emplace(i);

    int count = 0;
    while (!queue.empty()) {
      int u = queue.front();
      queue.pop();
      ++count;

      for (int v : dependency_graph[u]) {
        --indegree[v];
        if (indegree[v] == 0) queue.emplace(v);
      }
    }
    return count == numCourses;
  }
};

}  // namespace fast