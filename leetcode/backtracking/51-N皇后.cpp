#include <bits/stdc++.h>

class NQueensSolver {
public:
  std::vector<std::vector<std::string>> Solve(int n) {
    n_ = n;
    positions_.resize(n_);
    Backtracking(0);
    return std::move(slns_);
  }

  void Backtracking(int step) {
    if (step == positions_.size()) {
      AppendSln();
    } else {
      for (int i = 0; i < n_; i++) {
        positions_[step] = i;
        if (IsValid(step)) {
          Backtracking(step + 1);
        }
      }
    }
  }

  bool IsValid(int step) {
    for (int i = 0; i < step; i++) {
      if (positions_[step] == positions_[i] || std::abs(step - i) == std::abs(positions_[step] - positions_[i])) {
        return false;
      }
    }
    return true;
  }

  void AppendSln() {
    std::vector<std::string> sln(n_, std::string(n_, '.'));
    for (int i = 0; i < n_; i++) {
      sln[i][positions_[i]] = 'Q';
    }
    slns_.emplace_back(std::move(sln));
  }

private:
  int n_; ///< the size of board
  std::vector<int> positions_;
  std::vector<std::vector<std::string>> slns_;
};