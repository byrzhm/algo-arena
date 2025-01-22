from typing import List


class Solution:
    def maxCoins(self, piles: List[int]) -> int:
        piles.sort(reverse=True)
        n = len(piles)
        ans = sum(piles[i] for i in range(1, 2 * n // 3, 2))
        return ans
