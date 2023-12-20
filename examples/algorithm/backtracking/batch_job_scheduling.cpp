#include <bits/stdc++.h>

constexpr auto INF = 0x3f3f3f3f;

class BatchJobScheduling {
 public:
  /**
   * @brief 解决批处理作业调度问题
   */
  void Solve() {
    Backtracking(0);
    std::cout << bestf_ << '\n';
    for (int i = 0; i < n_; i++) {
      std::cout << bestx_[i] << " ";
    }
    std::cout << std::endl;
  }

  /**
   * @brief 回溯法求解批处理作业调度问题
   * 
   * @param step 当前处理的作业
   */
  void Backtracking(int step) {
    if (step == n_) {
      bestx_ = x_;
      bestf_ = f_;
      return;
    }

    int prev_f2 = (step > 0) ? f2_[step - 1] : 0; // 机器2处理完前一个作业的完成处理时间
    for (int i = step; i < n_; i++) {
      f1_ += time_[x_[i]][0]; // 机器1处理完第i个作业的完成处理时间
      f2_[step] = ((prev_f2 > f1_) ? prev_f2 : f1_) + time_[x_[i]][1]; // 机器2处理完第i个作业的完成处理时间
      f_ += f2_[step]; // 完成时间和
      if (f_ < bestf_) { // 剪枝
        std::swap(x_[step], x_[i]); // 交换
        Backtracking(step + 1);
        std::swap(x_[step], x_[i]); // 回溯
      }
      // 回溯
      f1_ -= time_[x_[i]][0]; 
      f_ -= f2_[step];
    }
  }

  /**
   * @brief 初始化
   */
  void Init() {
    std::cin >> n_;
    for (int i = 0; i < n_; i++) {
      int t1, t2;
      std::cin >> t1 >> t2;
      time_.push_back({t1, t2});
    }

    f_ = f1_ = 0;
    bestf_ = INF;

    f2_.resize(n_, 0);
    x_.resize(n_);
    for (int i = 0; i < n_; i++) {
      x_[i] = i;
    }
  }

 private:
  std::vector<std::vector<int>> time_;  ///< 各作业需要的处理时间
  std::vector<int> x_;                  ///< 当前作业调度
  std::vector<int> bestx_;              ///< 当前最优作业调度
  std::vector<int> f2_;                 ///< 机器2处理完第i个作业的完成处理时间
  int f1_;                              ///< 机器1完成处理时间
  int f_;                               ///< 完成时间和
  int bestf_;                           ///< 当前最优值
  int n_;                               ///< 作业数
};

int main() {
  BatchJobScheduling bjs;
  bjs.Init();
  bjs.Solve();
}