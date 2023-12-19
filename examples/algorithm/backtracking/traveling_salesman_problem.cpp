#include <bits/stdc++.h>

constexpr auto INF = 0x3f3f3f3f;

class TravelingSalesmanProblemSolver {
 public:
  TravelingSalesmanProblemSolver() = delete;
  explicit TravelingSalesmanProblemSolver(const std::vector<std::vector<int>> &graph)
      : graph_(graph), n_(graph.size()) {
    current_path_.reserve(n_);
    for (int i = 0; i < n_; i++) {
      current_path_[i] = i;
    }
  }

  int Solve() {
    Backtracking(1); /* 总是从0号城市开始 */
    return best_weight_;
  }

  void Backtracking(int step) {
    if (step == n_ - 1) { /* 已经搜索到叶节点, 已经选择了最后一个城市 */
      if (graph_[current_path_[n_ - 1]][current_path_[n_ - 2]] != INF && graph_[current_path_[n_ - 1]][0] != INF) {
        if (current_weight_ + graph_[current_path_[n_ - 1]][current_path_[n_ - 2]] + graph_[current_path_[n_ - 1]][0] <
            best_weight_) { /* 当前回路更优, 更新最优搜索结果 */
          best_weight_ =
              current_weight_ + graph_[current_path_[n_ - 2]][current_path_[n_ - 1]] + graph_[current_path_[n_ - 1]][0];
          best_path_ = current_path_;
        }
      }

    } else { /* 如果搜索没有到叶节点, 当前得到的部分路径
              <0, current_path_[1], ..., current_path_[step - 1], ?, ..., ?>*/
      for (int i = step; i < n_; i++) {
        if (graph_[current_path_[step - 1]][current_path_[i]] != INF &&
            current_weight_ + graph_[current_path_[step - 1]][current_path_[i]] < best_weight_) {
          std::swap(current_path_[step], current_path_[i]); /* 加入第i个城市 */
          current_weight_ =
              current_weight_ + graph_[current_path_[step - 1]][current_path_[step]]; /* 更新扩展之后的路径代价 */
          Backtracking(step + 1); /* 递归搜索以 current_path_[i] 为根的后续子树 */
          current_weight_ = current_weight_ - graph_[current_path_[step - 1]][current_path_[step]]; /* 回溯 */
          std::swap(current_path_[step], current_path_[i]);
        }
      }
    }
  }

 private:
  int n_;                                       ///< 节点数
  int current_weight_{0};                       ///< 当前权值
  int best_weight_{INF};                        ///< 当前最佳权值
  std::vector<int> current_path_;               ///< 当前路径
  std::vector<int> best_path_;                  ///< 当前最佳路径
  const std::vector<std::vector<int>> &graph_;  ///< 图: 邻接矩阵表示法
};

int main() {
  int n;  ///< 城市数量
  std::cin >> n;
  std::vector<std::vector<int>> graph(n, std::vector<int>(n, INF));

  for (int i = 0; i < n; i++) {
    graph[i][i] = 0;
  }

  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      int w;
      std::cin >> w;
      graph[i][j] = w;
      graph[j][i] = w;
    }
  }

  TravelingSalesmanProblemSolver solver(graph);
  std::cout << solver.Solve() << std::endl;
}