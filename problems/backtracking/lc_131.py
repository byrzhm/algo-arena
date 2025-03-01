from typing import List


class Solution:
    def partition(self, s: str) -> List[List[str]]:
        ans = []
        path = []
        n = len(s)

        def dfs(step: int):
            if step == n:
                ans.append(path.copy())
                return

            for i in range(step, n):
                t = s[step : i + 1]
                if t == t[::-1]:
                    path.append(t)
                    dfs(i + 1)
                    path.pop()

        dfs(0)
        return ans
