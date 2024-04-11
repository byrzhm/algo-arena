from typing import List
from math import gcd

MAX = 51
coprime = [[j for j in range(1, MAX) if gcd(i, j) == 1]
            for i in range(MAX)]

class Solution:
    def getCoprimes(self, nums: List[int], edges: List[List[int]]) -> List[int]:
        n = len(nums)
        ans = [-1] * n
        adj = [[] for _ in range(n)]

        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)

        cache = [(-1, -1)] * MAX

        def dfs(i, fa, depth):
            val = nums[i]
            ans[i] = max(cache[j] for j in coprime[val])[1]
            save = cache[val]
            cache[val] = (depth, i)

            for j in adj[i]:
                if j != fa:
                    dfs(j, i, depth + 1)
            
            cache[val] = save

        dfs(0, -1, 0)
        return ans