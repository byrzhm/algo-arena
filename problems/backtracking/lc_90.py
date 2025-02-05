from typing import List


class Solution:
    def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        ans = []
        path = []
        n = len(nums)

        def dfs(i: int) -> None:
            if i == n:
                ans.append(path.copy())
                return

            x = nums[i]

            # case 1: 不要
            # 如果不要那么后面相同的都不要
            j = i + 1
            while j < n and nums[j] == x:
                j += 1
            dfs(j)

            # case 2: 要
            path.append(x)
            dfs(i + 1)
            path.pop()  # 恢复现场

        dfs(0)

        return ans
