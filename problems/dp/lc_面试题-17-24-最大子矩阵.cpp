#include <bits/stdc++.h>

class Solution {
 public:
  std::vector<int> getMaxMatrix(std::vector<std::vector<int>> &matrix) {
    std::vector<std::vector<int>> &prefix = matrix;
    setPrefix(prefix);

    std::vector<int> sums(r);
    std::array<int, 2> rowPos;
    std::array<int, 2> colPos;
    std::array<int, 2> tmpRowPos;
    int maxSum = std::numeric_limits<int>::min();
    int currSum;
    for (int j = 0; j < c; j++) {
      for (int k = j; k < c; k++) {
        for (int i = 0; i < r; i++) {
          if (j == 0)
            sums[i] = prefix[i][k];
          else
            sums[i] = prefix[i][k] - prefix[i][j - 1];
        }
        currSum = getMaxSubSum(sums, tmpRowPos);
        if (currSum > maxSum) {
          rowPos.swap(tmpRowPos);
          maxSum = currSum;
          colPos = {j, k};
        }
      }
    }
    return {rowPos[0], colPos[0], rowPos[1], colPos[1]};
  }

 private:
  int getMaxSubSum(std::vector<int> const &v, std::array<int, 2> &ret) {
    int sum = v[0];
    int maxSum = v[0];
    int &begin = ret[0];
    int &end = ret[1];
    int tmp = 0;
    begin = 0;
    end = 0;

    for (int i = 1; i < r; i++) {
      if (sum > 0) {
        sum += v[i];
      } else {
        sum = v[i];
        tmp = i;
      }
      if (sum > maxSum) {
        maxSum = sum;
        begin = tmp;
        end = i;
      }
    }
    return maxSum;
  }

  void setPrefix(std::vector<std::vector<int>> &matrix) {
    r = matrix.size();
    c = matrix[0].size();
    std::vector<std::vector<int>> &prefix = matrix;

    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (j > 0) prefix[i][j] = prefix[i][j - 1] + matrix[i][j];
      }
    }
  }

 private:
  int r;
  int c;
};

int main() {
  // [[-1, -2, -9, 6], [8, -9, -3, -6], [2, 9, -7, -6]]
  std::vector<std::vector<int>> matrix{{-1, -2, -9, 6}, {8, -9, -3, -6}, {2, 9, -7, -6}};

  auto ret = Solution().getMaxMatrix(matrix);
  std::cout << ret[0] << " " << ret[1] << " " << ret[2] << " " << ret[3] << std::endl;

  return 0;
}