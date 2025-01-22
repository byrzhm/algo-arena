from typing import List
from functools import cache
from itertools import accumulate

"""
对于一个栈（数组），我们只能移除其前缀。注意题目说数组 piles[i] 从左到右表示栈顶到栈底。
对每个栈求前缀和 s，其中 s[w] 表示一个体积为 w+1，价值为 s[w] 的物品。

问题转化成：
从 n 个物品组中选物品，每组至多选一个物品（可以不选），要求体积总和至多为 k，求物品价值总和的最大值。

⚠️注意：对于本题来说，由于元素值都是非负数，且一定可以选 k 个硬币，所以「至多」和「恰好」计算出来的结果是一样的。为方便写代码这里用至多。




类似 0-1 背包，定义 dfs(i,j) 表示从 piles[0] 到 piles[i] 中，选体积之和至多为 j 的物品时，物品价值之和的最大值。

枚举第 i 组的所有物品（枚举前缀和），设当前物品体积为 w，价值为 v，那么问题变成从前 i−1 个物品组中，选体积之和至多为 j−w 的物品时，物品价值之和的最大值，即 dfs(i−1,j−w)，加上 v 得到 dfs(i,j)。

所有情况取最大值，得

dfs(i,j) = (v,w) max(dfs(i−1,j−w)+v)
如果该组不选物品，则上式中的 v=w=0。

递归边界：dfs(−1,j)=0。

递归入口：dfs(n−1,k)，这是原问题，也是答案。
"""


class Solution:
    def maxValueOfCoins(self, piles: List[List[int]], k: int) -> int:
        @cache  # 缓存装饰器，避免重复计算 dfs 的结果（记忆化）
        def dfs(i: int, j: int) -> int:
            if i < 0:
                return 0
            # 不选这一组中的任何物品
            res = dfs(i - 1, j)
            # 枚举选哪个
            for w, v in enumerate(accumulate(piles[i][:j]), 1):
                res = max(res, dfs(i - 1, j - w) + v)
            return res

        return dfs(len(piles) - 1, k)


class Solution:
    def maxValueOfCoins(self, piles: List[List[int]], k: int) -> int:
        n = len(piles)
        # f[i][j]: 前 i 个 pile 中选至多 j 个
        f = [[0] * (k + 1) for _ in range(n + 1)]
        for i in range(1, n + 1):
            for j in range(1, k + 1):
                f[i][j] = f[i - 1][j]
                for w, v in enumerate(accumulate(piles[i - 1][:j]), 1):
                    f[i][j] = max(f[i][j], f[i - 1][j - w] + v)
        return f[n][k]


piles = [[1, 100, 3], [7, 8, 9]]
k = 2
assert Solution().maxValueOfCoins(piles, k) == 101
