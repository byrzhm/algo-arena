from typing import List
from functools import cache


# DP
class Solution:
    def findBall(self, grid: List[List[int]]) -> List[int]:
        n_rows, n_cols = len(grid), len(grid[0])

        @cache
        def dfs(row: int, col: int) -> int:
            if row == n_rows:
                return col

            if grid[row][col] == 1:
                return (
                    dfs(row + 1, col + 1)
                    if col + 1 < n_cols and grid[row][col + 1] == 1
                    else -1
                )
            else:
                return (
                    dfs(row + 1, col - 1)
                    if col - 1 >= 0 and grid[row][col - 1] == -1
                    else -1
                )

        return [dfs(0, col) for col in range(n_cols)]


# 模拟
class Solution:
    def findBall(self, grid: List[List[int]]) -> List[int]:
        n = len(grid[0])
        ans = [-1] * n
        for j in range(n):
            col = j  # 球的初始列
            for row in grid:
                dir = row[col]
                col += dir  # 移动球
                if col < 0 or col == n or row[col] != dir:  # 到达侧边或 V 形
                    break
            else:  # 成功到达底部
                ans[j] = col
        return ans
