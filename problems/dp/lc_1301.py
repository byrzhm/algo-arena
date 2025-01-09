from typing import List


# fmt: off
class Solution:
    def pathsWithMaxScore(self, board: List[str]) -> List[int]:
        MOD = 1_000_000_007
        n = len(board)
        dp = [[[0, 0] for _ in range(n)] for _ in range(n)]
        dp[-1][-1][1] = 1

        for i in range(n - 2, -1, -1):
            if board[i][-1] == "X":
                break
            dp[i][-1][0] = dp[i + 1][-1][0] + int(board[i][-1])
            dp[i][-1][1] = 1

        for j in range(n - 2, -1, -1):
            if board[-1][j] == "X":
                break
            dp[-1][j][0] = dp[-1][j + 1][0] + int(board[-1][j])
            dp[-1][j][1] = 1

        for i in range(n - 2, -1, -1):
            for j in range(n - 2, -1, -1):
                if board[i][j] == "X":
                    continue
                p1, p2, p3 = sorted([dp[i][j + 1], dp[i + 1][j], dp[i + 1][j + 1]])

                val = 0 if i == 0 and j == 0 else int(board[i][j])

                if p3[0] != p2[0]:
                    dp[i][j][0] = p3[0] + val
                    dp[i][j][1] = p3[1]
                elif p1[0] != p2[0]:
                    dp[i][j][0] = p3[0] + val
                    dp[i][j][1] = p3[1] + p2[1]
                elif p1[0] != 0:
                    dp[i][j][0] = p3[0] + val
                    dp[i][j][1] = p3[1] + p2[1] + p1[1]
                elif p3[1] > 0:
                    dp[i][j][0] = val
                    dp[i][j][1] = p3[1]
        return [dp[0][0][0] % MOD, dp[0][0][1] % MOD]
# fmt: on
