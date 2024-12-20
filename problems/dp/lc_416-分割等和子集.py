from typing import List

"""

转化为0-1背包问题

背包大小为 sum(nums) // 2

dp[i][j] 背包大小为 i, 前 j 个物品

"""
class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        total = sum(nums)
        if total % 2 != 0:
            return False
        
        capacity = total // 2
        n = len(nums)
        dp = [[0] * (n + 1) for _ in range(capacity + 1)]

        for i in range(1, capacity + 1):
            for j in range(1, n + 1):
                if nums[j - 1] <= i:
                    dp[i][j] = max(dp[i][j - 1], dp[i - nums[j - 1]][j - 1] + nums[j - 1])
                else:
                    dp[i][j] = dp[i][j - 1]

        return dp[capacity][n] == capacity


print(Solution().canPartition([2, 1, 1, 2]))
        
"""

创建二维数组 dp，包含 target+1 行与 n+1 列，其中 dp[i][j] 表示从数组的前 j 个数内选取若干个正整数（可以是 0 个），
是否存在一种选取方案使得被选取的正整数的和等于 i。初始时，dp 中的全部元素都是 false。

"""
class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        n = len(nums)
        if n < 2:
            return False
        
        total = sum(nums)
        if total % 2 != 0:
            return False
        
        target = total // 2
        dp = [[False] * (n + 1) for _ in range(target + 1)]
        
        dp[0][0] = True

        for i in range(1, target + 1):
            for j in range(1, n + 1):
                if nums[j - 1] <= i:
                    dp[i][j] = dp[i][j - 1] | dp[i - nums[j - 1]][j - 1]
                else:
                    dp[i][j] = dp[i][j - 1]

        return dp[target][n]

print(Solution().canPartition([2, 1, 1, 2]))


"""

还可以继续优化，使用一维数组进行优化空间

nums 对应于行
target 对应于列

"""

class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        n = len(nums)
        if n < 2:
            return False
        
        total = sum(nums)
        if total % 2 != 0:
            return False
        
        target = total // 2
        dp = [True] + [False] * target

        for i, x in enumerate(nums):
            for j in range(target, x - 1, -1):
                dp[j] = dp[j] | dp[j - x]

        return dp[target]

print(Solution().canPartition([2, 1, 1, 2]))