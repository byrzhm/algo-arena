from typing import List


class Solution:
    def maximumWhiteTiles(self, tiles: List[List[int]], carpetLen: int) -> int:
        tiles.sort()  # 按照起始位置排序
        n = len(tiles)
        res = 0  # 最多可以覆盖的瓷砖数量
        cnt = 0  # 当前可以完全覆盖的连续瓷砖段的瓷砖数总和
        r = 0  # 从左至右第一段无法完全覆盖的连续瓷砖的下标
        # 枚举起始点对应连续瓷砖段的下标
        for l in range(n):
            if l:
                cnt -= tiles[l - 1][1] - tiles[l - 1][0] + 1
            while r < n and tiles[l][0] + carpetLen > tiles[r][1]:
                cnt += tiles[r][1] - tiles[r][0] + 1
                r += 1
            if r == n:
                # 此时无法通过右移增加覆盖瓷砖数，更新最大值并返回即可
                res = max(res, cnt)
                return res
            extra = max(
                0, tiles[l][0] + carpetLen - tiles[r][0]
            )  # 当前无法完全覆盖的连续瓷砖段的覆盖瓷砖数
            res = max(res, cnt + extra)
        return res
