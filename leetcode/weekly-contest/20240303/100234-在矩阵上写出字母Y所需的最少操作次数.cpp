#include <vector>
using std::vector;
using std::unordered_map;

class Solution
{
public:
  int minimumOperationsToWriteY(vector<vector<int>> &grid)
  {
    n = grid.size();

    unordered_map<int, int> countY;
    unordered_map<int, int> countNotY;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (inY(i, j)) {
          ++countY[grid[i][j]];
        } else {
          ++countNotY[grid[i][j]];
        }
      }
    }

    int minOp    = 0x3f3f3f3f;
    int ySize    = n / 2 + n / 2 + n / 2 + 1;
    int notYSize = n * n - ySize;
    for (int i = 0; i <= 2; ++i) {
      int flipY = ySize - countY[i];  // Y is all i
      for (int j = 0; j <= 2; ++j) {
        if (j != i) {
          int flipNotY = notYSize - countNotY[j];
          int ops      = flipY + flipNotY;
          if (ops < minOp) {
            minOp = ops;
          }
        }
      }
    }

    return minOp;
  }

  bool inY(int i, int j)
  {
    if (j == n / 2 && i >= n / 2)
      return true;
    if (i == j && i <= n / 2)
      return true;
    if (i + j == n - 1 && i <= n / 2)
      return true;
    return false;
  }

  int n;
};