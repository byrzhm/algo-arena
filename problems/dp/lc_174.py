from typing import List


# Wrong Solution:
#   Violates the principle of no aftereffect in dynamic programming
#   See https://leetcode.cn/problems/dungeon-game/solutions/326171/di-xia-cheng-you-xi-by-leetcode-solution
class Solution:
    def calculateMinimumHP(self, dungeon: List[List[int]]) -> int:
        m, n = len(dungeon), len(dungeon[0])
        f = [[[0, 0] for _ in range(n)] for _ in range(m)]
        if dungeon[0][0] >= 0:
            f[0][0] = [1, 1 + dungeon[0][0]]
        else:
            f[0][0] = [1 - dungeon[0][0], 1]
        for i in range(1, m):
            # if dungeon[i][0] >= 0:
            #     f[i][0][0] = f[i - 1][0][0]
            #     f[i][0][1] = f[i - 1][0][1] + dungeon[i][0]
            # else:
            #     if f[i - 1][0][1] > -dungeon[i][0]:
            #         f[i][0][0] = f[i - 1][0][0]
            #         f[i][0][1] = f[i - 1][0][1] + dungeon[i][0]
            #     else:
            #         f[i][0][0] = f[i - 1][0][0] + 1 + (-dungeon[i][0] - f[i - 1][0][1])
            #         f[i][0][1] = 1
            f[i][0][0] = f[i - 1][0][0] + max(0, 1 - dungeon[i][0] - f[i - 1][0][1])
            f[i][0][1] = max(1, f[i - 1][0][1] + dungeon[i][0])

        for j in range(1, n):
            f[0][j][0] = f[0][j - 1][0] + max(0, 1 - dungeon[0][j] - f[0][j - 1][1])
            f[0][j][1] = max(1, f[0][j - 1][1] + dungeon[0][j])

        for i in range(1, m):
            for j in range(1, n):
                x1 = f[i][j - 1][0] + max(0, 1 - dungeon[i][j] - f[i][j - 1][1])
                y1 = max(1, f[i][j - 1][1] + dungeon[i][j])
                x2 = f[i - 1][j][0] + max(0, 1 - dungeon[i][j] - f[i - 1][j][1])
                y2 = max(1, f[i - 1][j][1] + dungeon[i][j])
                if (x1, -y1) < (x2, -y2):
                    f[i][j] = [x1, y1]
                else:
                    f[i][j] = [x2, y2]
        return f[-1][-1][0]


# Accepted Solution
class Solution:
    def calculateMinimumHP(self, dungeon: List[List[int]]) -> int:
        m, n = len(dungeon), len(dungeon[0])
        f = [[0] * n for _ in range(m)]
        f[-1][-1] = max(1, 1 - dungeon[-1][-1])
        for i in range(m - 2, -1, -1):
            f[i][-1] = max(1, f[i + 1][-1] - dungeon[i][-1])
        for j in range(n - 2, -1, -1):
            f[-1][j] = max(1, f[-1][j + 1] - dungeon[-1][j])
        for i in range(m - 2, -1, -1):
            for j in range(n - 2, -1, -1):
                f[i][j] = max(1, min(f[i + 1][j], f[i][j + 1]) - dungeon[i][j])
        return f[0][0]
