#include <unordered_set>

namespace normal {

class Solution
{
public:
  void setZeroes(std::vector<std::vector<int>> &matrix)
  {
    std::unordered_set<int> zeroRows;
    std::unordered_set<int> zeroCols;
    int r = matrix.size();
    int c = matrix[0].size();
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        if (matrix[i][j] == 0) {
          zeroRows.emplace(i);
          zeroCols.emplace(j);
        }
      }
    }

    for (auto row : zeroRows) {
      for (int col = 0; col < c; ++col) {
        matrix[row][col] = 0;
      }
    }

    for (auto col : zeroCols) {
      for (int row = 0; row < r; ++row) {
        matrix[row][col] = 0;
      }
    }
  }
};

}  // namespace normal