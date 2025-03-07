from typing import List
from collections import defaultdict


class Solution:
    def beautifulSubsets(self, nums: List[int], k: int) -> int:
        ans = -1
        path = []
        n = len(nums)

        def dfs(i: int) -> None:
            nonlocal ans
            if i == n:
                ans += 1
                # print(path)
                return

            x = nums[i]
            if x + k not in path and x - k not in path:
                path.append(x)
                dfs(i + 1)
                path.pop()
            dfs(i + 1)

        dfs(0)

        return ans


class Solution:
    def beautifulSubsets(self, nums: List[int], k: int) -> int:
        ans = -1
        cnt = defaultdict(int)
        n = len(nums)

        def dfs(i: int) -> None:
            nonlocal ans
            if i == n:
                ans += 1
                # print(path)
                return

            x = nums[i]
            if cnt[x + k] == 0 and cnt[x - k] == 0:
                cnt[x] += 1
                dfs(i + 1)
                cnt[x] -= 1
            dfs(i + 1)

        dfs(0)

        return ans
