#include <bits/stdc++.h>

struct Repository {
  int id_;
  int superid_;
  std::vector<int> vec_;

  bool operator<(const Repository &other) const {
    int dim = vec_.size();
    for (int i = 0; i < dim; i++) {
      if (vec_[i] >= other.vec_[i]) {
        return false;
      }
    }
    return true;
  }
};

int main()
{
  int total, dim;
  std::cin >> total >> dim;

  std::map<int, int> super_map;
  std::vector<Repository> repos(total);

  for (int i = 0; i < total; i++) {
    repos[i].id_ = i + 1;
    for (int j = 0; j < dim; j++) {
      int tmp;
      std::cin >> tmp;
      repos[i].vec_.emplace_back(tmp);
    }
  }

  for (int i = 0; i < total; i++) {
    repos[i].superid_ = 0;
    for (int j = 0; j < total; j++) {
      if (repos[i] < repos[j]) {
        repos[i].superid_ = repos[j].id_;
        break;
      }
    }
  }

  for (auto &repo : repos) {
    std::cout << repo.superid_ << "\n";
  }

}