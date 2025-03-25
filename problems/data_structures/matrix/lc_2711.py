from typing import List
from collections import defaultdict

"""
对角线遍历

mxn

0,0  0,1  0,2  0,3
1,0  1,1  1,2  1,3
2,0  2,1  2,2  2,3

for i in range(m):
    # start at i,0
    x, y = i, 0
    while x < m and y < n:
        # do something at x,y
        x, y = x + 1, y + 1
for j in range(1, n):
    # start at 0,j
    x, y = 0, j
    while x < m and y < n:
        # do something at x,y
        x, y = x + 1, y + 1

"""


class Solution:
    def differenceOfDistinctValues(self, grid: List[List[int]]) -> List[List[int]]:
        m, n = len(grid), len(grid[0])
        ans = [[0] * n for _ in range(m)]
        topLeft = defaultdict(int)
        bottomRight = defaultdict(int)

        for i in range(m):
            # start at i,0
            topLeft.clear()
            bottomRight.clear()

            x, y = i, 0
            while x < m and y < n:
                t = grid[x][y]
                bottomRight[t] += 1
                x, y = x + 1, y + 1

            x, y = i, 0
            while x < m and y < n:
                t = grid[x][y]
                bottomRight[t] -= 1
                if bottomRight[t] == 0:
                    del bottomRight[t]
                ans[x][y] = abs(len(bottomRight) - len(topLeft))
                topLeft[t] += 1
                x, y = x + 1, y + 1

        for j in range(1, n):
            # start at 0,j
            topLeft.clear()
            bottomRight.clear()

            x, y = 0, j
            while x < m and y < n:
                t = grid[x][y]
                bottomRight[t] += 1
                x, y = x + 1, y + 1

            x, y = 0, j
            while x < m and y < n:
                t = grid[x][y]
                bottomRight[t] -= 1
                if bottomRight[t] == 0:
                    del bottomRight[t]
                ans[x][y] = abs(len(bottomRight) - len(topLeft))
                topLeft[t] += 1
                x, y = x + 1, y + 1

        return ans
