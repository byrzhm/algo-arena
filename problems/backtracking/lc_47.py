from typing import List


class Solution:
    def permuteUnique(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        ans = []
        path = []
        vis = [0] * n
        nums.sort()

        def dfs(idx: int) -> None:
            if idx == n:
                ans.append(path.copy())
                return

            for i in range(n):
                if vis[i] or (i > 0 and nums[i] == nums[i - 1] and not vis[i - 1]):
                    continue

                path.append(nums[i])
                vis[i] = 1
                dfs(idx + 1)
                vis[i] = 0
                path.pop()

        dfs(0)
        return ans
