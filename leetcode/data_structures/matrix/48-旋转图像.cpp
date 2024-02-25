#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

namespace first {

class Solution
{
public:
  void rotate(std::vector<std::vector<int>> &matrix)
  {
    int n     = matrix.size();
    int left  = 0;
    int right = n - 1;

    while (left < right) {
      for (int i = 0; i < right - left; ++i) {
        int bottom          = right;
        int top             = left;

        int &theTopLeft     = matrix[top][left + i];
        int &theTopRight    = matrix[top + i][right];
        int &theBottomRight = matrix[bottom][right - i];
        int &theBottomLeft  = matrix[bottom - i][left];

        int saveTopLeft     = theTopLeft;      // 保存左上角的数

        theTopLeft          = theBottomLeft;   // 左下角移到左上角
        theBottomLeft       = theBottomRight;  // 右下角移到左下角
        theBottomRight      = theTopRight;     // 右上角移到右下角
        theTopRight         = saveTopLeft;     // 右上角赋值为保存的值
      }

      ++left;
      --right;
    }
  }
};

}  // namespace first

namespace second {

class Solution
{
public:
  // 先转置，再镜像对称
  void rotate(std::vector<std::vector<int>> &matrix)
  {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        std::swap(matrix[i][j], matrix[j][i]);
      }
    }

    int half = n >> 1;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < half; ++j) {
        std::swap(matrix[i][j], matrix[i][n - j]);
      }
    }
  }
};

}  // namespace second


std::ostream &operator<<(std::ostream &stream, std::vector<std::vector<int>> &matrix)
{
  for (const auto &row : matrix) {
    for (int value : row) {
      stream << value << " ";
    }
    stream << "\n";
  }
  return stream;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<std::vector<int>> matrix{
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
  };

  first::Solution().rotate(matrix);

  std::cout << matrix << '\n';
  return 0;
}