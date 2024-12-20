from typing import List

class Solution:
    def longestPath(self, parent: List[int], s: str) -> int:
        n = len(parent)
        adj = [[] for _ in range(n)]

        for i in range(1, n):
            p = parent[i]
            adj[p].append(i)
        
        ans = 1

        def dfs(i): # adj 中没有父节点，如果有需要在参数里加 father 以供判断
            nonlocal ans

            first, second = 0, 0
            for j in adj[i]:
                second = dfs(j)
                if s[j] != s[i]:
                    ans = max(ans, first + second + 1)
                    first = max(first, second)
            return first + 1

        dfs(0)
        return ans