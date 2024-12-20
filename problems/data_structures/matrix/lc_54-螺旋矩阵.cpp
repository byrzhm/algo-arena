#include <vector>

class Solution
{
public:
  enum class Direction
  {
    right,
    down,
    left,
    up,
  };

  std::vector<int> spiralOrder(std::vector<std::vector<int>> &matrix)
  {
    int r = matrix.size();
    int c = matrix[0].size();
    std::vector<int> ans;
    ans.reserve(r * c);

    int rowMin    = 0;
    int rowMax    = r - 1;
    int colMin    = 0;
    int colMax    = c - 1;

    Direction dir = Direction::right;

    while (rowMax - rowMin >= 0 && colMax - colMin >= 0) {
      switch (dir) {
        case Direction::right:
          for (int i = rowMin, j = colMin; j <= colMax; ++j) {
            ans.emplace_back(matrix[i][j]);
          }
          ++rowMin;
          dir = Direction::down;
          break;

        case Direction::down:
          for (int i = rowMin, j = colMax; i <= rowMax; ++i) {
            ans.emplace_back(matrix[i][j]);
          }
          --colMax;
          dir = Direction::left;
          break;

        case Direction::left:
          for (int i = rowMax, j = colMax; j >= colMin; --j) {
            ans.emplace_back(matrix[i][j]);
          }
          --rowMax;
          dir = Direction::up;
          break;

        case Direction::up:
          for (int i = rowMax, j = colMin; i >= rowMin; --i) {
            ans.emplace_back(matrix[i][j]);
          }
          ++colMin;
          dir = Direction::right;
          break;
      }
    }
    return ans;
  }
};