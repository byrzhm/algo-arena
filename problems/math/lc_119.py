from typing import List

"""
Pascal's Triangle - 杨辉三角

第 i 行 (从 0 开始) 是 Comb(i, 0), Comb(i, 1), ..., Comb(i, i)
"""

f = [[1] * i for i in range(1, 35)]
for i in range(2, 34):
    for j in range(1, i):
        f[i][j] = f[i - 1][j - 1] + f[i - 1][j]


class Solution:
    def getRow(self, rowIndex: int) -> List[int]:
        return f[rowIndex]
