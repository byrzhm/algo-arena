#include <bits/stdc++.h>

class MColoringProblem {
 public:
  /**
   * @brief 解决m着色问题
   */
  void Solve() {
    Backtracking(0);
    if (sum_ > 0) {
      // std::cout << "可行解的数目为" << sum_ << '\n';
      for (int i = 0; i < n_; i++) {
        std::cout << bestx_[i] << " ";
      }
      std::cout << std::endl;
    } else {
      std::cout << "没有可行解" << std::endl;
    }
  }

  /**
   * @brief 回溯法求解m着色问题
   *
   * @param step 当前处理的顶点
   */
  void Backtracking(int step) {
    if (step == n_) {
      if (sum_ == 0) {
        bestx_ = x_;
      }
      sum_++;
      return;
    }

    for (int i = 1; i <= m_; i++) {
      x_[step] = i;
      if (Check(step)) {
        Backtracking(step + 1);
      }
    }
  }

  /**
   * @brief 检查顶点step的着色是否合法
   *
   * @param step 当前处理的顶点
   * @return true 合法
   * @return false 不合法
   */
  bool Check(int step) {
    for (int i = 0; i < step; i++) {
      if ((graph_[i][step] != 0) && x_[i] == x_[step]) {
        return false;
      }
    }
    return true;
  }

  /**
   * @brief 初始化
   */
  void Init() {
    std::cin >> n_ >> m_;
    for (int i = 0; i < n_; i++) {
      std::vector<int> row(n_);
      for (int j = 0; j < n_; j++) {
        std::cin >> row[j]; // 1 表示相连, 0 表示不相连, ij相同无影响
      }
      graph_.push_back(row);
    }

    sum_ = 0;
    x_.resize(n_);
    bestx_.resize(n_);
  }

 private:
  int sum_;                              ///< 可行解的数目
  int n_;                                ///< 顶点数
  int m_;                                ///< 颜色数
  std::vector<std::vector<int>> graph_;  ///< 图
  std::vector<int> x_;                   ///< 当前着色
  std::vector<int> bestx_;               ///< 最优着色
};

int main() {
  MColoringProblem m_coloring_problem;
  m_coloring_problem.Init();
  m_coloring_problem.Solve();
  return 0;
}