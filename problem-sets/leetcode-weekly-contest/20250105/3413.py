from typing import List


class Solution:
    def maximumWhiteTiles(self, tiles: List[List[int]], carpetLen: int) -> int:
        n = len(tiles)
        res = cnt = r = 0
        for l in range(n):
            if l:
                cnt -= (tiles[l - 1][1] - tiles[l - 1][0] + 1) * tiles[l - 1][2]
            while r < n and tiles[l][0] + carpetLen > tiles[r][1]:
                cnt += (tiles[r][1] - tiles[r][0] + 1) * tiles[r][2]
                r += 1
            if r == n:
                res = max(res, cnt)
                return res
            extra = max(0, (tiles[l][0] + carpetLen - tiles[r][0]) * tiles[r][2])
            res = max(res, cnt + extra)
        return res

    def maximumCoins(self, coins: List[List[int]], k: int) -> int:
        coins.sort(key=lambda x: x[0])
        ans = self.maximumWhiteTiles(coins, k)

        coins.reverse()
        for t in coins:
            t[0], t[1] = -t[1], -t[0]
        return max(ans, self.maximumWhiteTiles(coins, k))
