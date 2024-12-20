from typing import List

class Solution:
    def unmarkedSumArray(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n = len(nums)
        sorted_range = sorted(range(n), key=lambda x: nums[x])
        pt = 0
        vis = [0] * n
        tot = sum(nums)
        ans = []
        for i, k in queries:
            if vis[i] == 0:
                vis[i] = 1
                tot -= nums[i]
            for _ in range(k):
                while pt < n and vis[sorted_range[pt]]:
                    pt += 1
                # 指针移到最后，表示已经删完，需要退出循环，否则空跑循环是不满足复杂度要求的——不过力扣现在还没卡
                if pt  == n: break
                p = sorted_range[pt]
                vis[p] = 1
                tot -= nums[p]
            ans.append(tot)
        return ans