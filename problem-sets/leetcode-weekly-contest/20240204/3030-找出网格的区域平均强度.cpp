#include <bits/stdc++.h>

/**
 * @brief very slow solution
 */
class Solution
{
public:
  std::vector<std::vector<int>> resultGrid(std::vector<std::vector<int>> &image, int threshold)
  {
    r        = image.size();
    c        = image[0].size();
    belongTo = std::vector<std::vector<std::vector<std::pair<int, int>>>>(
        r,
        std::vector<std::vector<std::pair<int, int>>>(c)
    );
    std::vector<std::vector<int>> result(image);
    std::vector<std::vector<int>> prefixSum = getPrefixSum(image);
    std::vector<std::vector<bool>> isArea   = findArea(image, threshold);
    std::vector<std::vector<int>> areaAvg   = getAreaAvg(isArea, prefixSum);

    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        if (!belongTo[i][j].empty()) {
          result[i][j] = 0;
          for (auto [ii, jj] : belongTo[i][j]) {
            result[i][j] += areaAvg[ii][jj];
          }
          result[i][j] /= belongTo[i][j].size();
        }
      }
    }

    return result;
  }

private:
  std::vector<std::vector<bool>> findArea(std::vector<std::vector<int>> &image, int threshold)
  {
    std::vector<std::vector<bool>> isArea(r, std::vector<bool>(c, false));
    for (int i = 0; i <= r - 3; ++i) {
      for (int j = 0; j <= c - 3; ++j) {
        if (isSubMatrixValid(image, i, j, threshold)) {
          isArea[i][j] = true;
          for (int ii = i; ii < i + 3; ++ii) {
            for (int jj = j; jj < j + 3; ++jj) {
              belongTo[ii][jj].emplace_back(i, j);
            }
          }
        }
      }
    }
    return isArea;
  }

  // 判断一个 3x3 子矩阵是否满足条件
  bool isSubMatrixValid(const std::vector<std::vector<int>> &matrix, int startRow, int startCol, int threshold)
  {
    for (int i = startRow; i < startRow + 2; ++i) {
      for (int j = startCol; j < startCol + 2; ++j) {
        int diffRow = std::abs(matrix[i + 1][j] - matrix[i][j]);
        int diffCol = std::abs(matrix[i][j + 1] - matrix[i][j]);

        if (diffRow > threshold || diffCol > threshold) {
          return false;
        }
      }
    }

    for (int i = startRow + 2, j = startCol; j < startCol + 2; ++j) {
      int diffCol = std::abs(matrix[i][j + 1] - matrix[i][j]);

      if (diffCol > threshold) {
        return false;
      }
    }

    for (int i = startRow, j = startCol + 2; i < startRow + 2; ++i) {
      int diffRow = std::abs(matrix[i + 1][j] - matrix[i][j]);

      if (diffRow > threshold) {
        return false;
      }
    }

    return true;
  }

  std::vector<std::vector<int>>
  getPrefixSum(std::vector<std::vector<int>> &image)
  {
    std::vector<std::vector<int>> prefixSum(r, std::vector<int>(c, 0));

    // 计算第一行的前缀和
    for (int j = 0; j < c; ++j) {
      prefixSum[0][j] = image[0][j];
      if (j > 0) {
        prefixSum[0][j] += prefixSum[0][j - 1];
      }
    }

    // 计算第一列的前缀和
    for (int i = 0; i < r; ++i) {
      prefixSum[i][0] = image[i][0];
      if (i > 0) {
        prefixSum[i][0] += prefixSum[i - 1][0];
      }
    }

    // 计算其余位置的前缀和
    for (int i = 1; i < r; ++i) {
      for (int j = 1; j < c; ++j) {
        prefixSum[i][j] = image[i][j] + prefixSum[i - 1][j] +
                          prefixSum[i][j - 1] - prefixSum[i - 1][j - 1];
      }
    }

    return prefixSum;
  }

  std::vector<std::vector<int>>
  getAreaAvg(std::vector<std::vector<bool>> &isArea, std::vector<std::vector<int>> &prefixSum)
  {
    std::vector<std::vector<int>> areaAvg(r, std::vector<int>(c, 0));

    auto getAreaSum = [&](int startRow, int startCol) {
      int endRow = startRow + 2;
      int endCol = startCol + 2;

      int sum    = prefixSum[endRow][endCol];

      if (startRow > 0) {
        sum -= prefixSum[startRow - 1][endCol];
      }

      if (startCol > 0) {
        sum -= prefixSum[endRow][startCol - 1];
      }

      if (startRow > 0 && startCol > 0) {
        sum += prefixSum[startRow - 1][startCol - 1];
      }

      return sum;
    };

    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        if (isArea[i][j]) {
          areaAvg[i][j] = getAreaSum(i, j) / 9;
        }
      }
    }
    return areaAvg;
  }

  int r;
  int c;
  std::vector<std::vector<std::vector<std::pair<int, int>>>> belongTo;
};

int main()
{
  int r                               = 3;
  int c                               = 3;
  std::vector<std::vector<int>> image = {
      {4, 8, 5},
      {5, 7, 7},
      {9, 4, 2}};

  int threshold = 4;
  auto result   = Solution().resultGrid(image, threshold);
  std::cout << "[\n";
  for (int i = 0; i < r; ++i) {
    std::cout << "  [";
    for (int j = 0; j < c; ++j) {
      std::cout << ' ' << result[i][j] << ',';
    }
    std::cout << "\b ],\n";
  }
  std::cout << "]\n";
}