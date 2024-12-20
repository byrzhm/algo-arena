from typing import List

"""

无向图求连通分量, 计算每个连通分量的边权按位与的结果

"""

class Solution:
    def minimumCost(self, n: int, edges: List[List[int]], query: List[List[int]]) -> List[int]:
        # 使用邻接表存图
        adj = [[] for _ in range(n)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))

        # 计算连通分量, 顺便计算连通分量中所有边权的按位与
        id = [-1] * n
        andWeights = []
        count = 0

        for i in range(n):
            if id[i] < 0:
                tand = -1
                
                q = []
                q.append(i)
                
                while len(q) > 0:
                    u = q.pop()
                    id[u] = count

                    for v, w in adj[u]:
                        tand &= w
                        if id[v] < 0:
                            q.append(v)

                count += 1
                andWeights.append(tand)

        # 根据之前计算的结果, 处理query
        ans = []
        for s, t in query:
            if s == t:
                ans.append(0)
            elif id[s] == id[t]:
                ans.append(andWeights[id[s]])
            else:
                ans.append(-1)

        return ans
