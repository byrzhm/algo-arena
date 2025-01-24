from typing import List
from functools import cache
from math import inf
from collections import deque


class Solution:
    def minimumCoins(self, prices: List[int]) -> int:
        n = len(prices)

        @cache
        def dfs(i: int):  # 购买第 i 个水果的前提下, 获得所有的水果所需要的最少金币
            if 2 * i >= n:
                return prices[i - 1]
            return prices[i - 1] + min(dfs(j) for j in range(i + 1, 2 * i + 2))

        return dfs(1)


# fmt: off
class Solution:
    def minimumCoins(self, prices: List[int]) -> int:
        f = list(prices)  # shallow copy
        n = len(prices)
        for i in range((n + 1) // 2 - 1, 0, -1):  # for all i >= (n + 1) // 2, f[i - 1] == prices[i - 1]
            f[i - 1] += min(f[i : i * 2 + 1])
        return f[0]
# fmt: on


"""
由于随着 i 的变小，j 的范围 [i+1,2i+1] 的左右边界也在变小，所以 [i+1,2i+1] 是一个向左的滑动窗口。
计算 min(dfs(j) for j in range(i + 1, 2 * i + 2)) 的过程可以使用单调队列进行优化
"""


class Solution:
    def minimumCoins(self, prices: List[int]) -> int:
        n = len(prices)
        q = deque([(n + 1, 0)])  # 哨兵, 保证后面半个的 DP 值为 prices 值本身
        for i in range(n, 0, -1):
            while q[-1][0] > i * 2 + 1:  # 右边离开窗口
                q.pop()
            f = prices[i - 1] + q[-1][1]
            while f <= q[0][1]:  # 保证最右边是最小的
                q.popleft()
            q.appendleft((i, f))  # 左边进入窗口
        return q[0][1]
