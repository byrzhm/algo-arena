from typing import List


class Solution:
    def generateMatrix(self, n: int) -> List[List[int]]:
        # direct = [[0, 1], [1, 0], [0, -1], [-1, 0]]
        dx = [0, 1, 0, -1]
        dy = [1, 0, -1, 0]
        res = [[0] * n for _ in range(n)]
        x, y = 0, 0
        st = 0
        for i in range(1, n * n + 1):
            res[x][y] = i
            if (
                x + dx[st] >= n
                or x + dx[st] < 0
                or y + dy[st] >= n
                or y + dy[st] < 0
                or res[x + dx[st]][y + dy[st]] != 0
            ):
                st = (st + 1) % 4
            x = x + dx[st]
            y = y + dy[st]
        return res
