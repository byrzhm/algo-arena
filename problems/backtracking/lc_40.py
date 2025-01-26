from typing import List


class Solution:
    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        candidates.sort()
        n = len(candidates)
        ans = []
        path = []

        def dfs(i: int, target: int) -> None:
            if target == 0:
                ans.append(path.copy())
                return

            # 没有可选的了
            if i == n:
                return

            # 所选的元素之和无法恰好等于 target
            x = candidates[i]
            if x > target:
                return

            # 选 x
            path.append(x)
            dfs(i + 1, target - x)
            path.pop()  # 恢复现场

            # 跳过相同的元素, 防止重复
            i += 1
            while i < n and candidates[i] == x:
                i += 1
            dfs(i, target)

        dfs(0, target)
        return ans
