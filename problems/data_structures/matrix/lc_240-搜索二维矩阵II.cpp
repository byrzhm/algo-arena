#include <iostream>
#include <vector>

class Solution
{
public:
  bool searchMatrix(std::vector<std::vector<int>> &matrix, int target)
  {
    int r = matrix.size();
    int c = matrix[0].size();

    // 从左下角开始，如果左下角的数比目标值要大，那么最下面一行就可以直接删除
    // 如果左下角的数要比目标值要小，那么最左边一列就可以删除

    int i = r - 1;
    int j = 0;

    while (i >= 0 && j < c) {
      if (matrix[i][j] == target)
        return true;

      if (matrix[i][j] > target) {
        --i;
      } else {
        ++j;
      }
    }

    return false;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<std::vector<int>> matrix{
      {1, 4, 7, 11, 15},
      {2, 5, 8, 12, 19},
      {3, 6, 9, 16, 22},
      {10, 13, 14, 17, 24},
      {18, 21, 23, 26, 30}
  };

  std::cout << (Solution().searchMatrix(matrix, 8) ? "true" : "false") << '\n';

  return 0;
}