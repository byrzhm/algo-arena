from typing import List

"""

dp[i][j] 表示前 j 个数，*包含和为 i 的子序列* 的子序列的数目

每个在前 j - 1 个数中 *包含和为 i 的子序列* 的子序列中，添加第 j 个数或不添加第 j 个数
都会生成 *包含和为 i 的子序列* 的子序列

如果 i >= 第 j 个数，还要考虑
    前 j 个数中 *包含和为 i - nums[j - 1] 的子序列* 的子序列的数目
    这些子序列加上第 j 个数，就成了 *包含和为 i 的子序列* 的子序列

dp[i][j]
    <- dp[i][j - 1] * 2 + dp[i - nums[j - 1]][j - 1]
        if i >= nums[j - 1]

    <- dp[i][j - 1] * 2
        if i < nums[j - 1]

! 包含和为 0 的子序列要注意

"""
class Solution:
    def sumOfPower(self, nums: List[int], k: int) -> int:
        MOD = 1_000_000_007
        n = len(nums)
        dp = [[0] * (n + 1) for _ in range(k + 1)]
        
        dp[0][0] = 1

        for i in range(0, k + 1):
            for j in range(1, n + 1):
                if nums[j - 1] <= i:
                    dp[i][j] = (dp[i][j - 1] * 2 + dp[i - nums[j - 1]][j - 1]) % MOD
                else:
                    dp[i][j] = (dp[i][j - 1] * 2) % MOD

        return dp[k][n]

if __name__ == '__main__':
    print(Solution().sumOfPower([1, 2, 3], 3))

"""

dp[i][j] 表示前 i 个数中，包含和为 j 的子序列的子序列的数目

"""
class Solution:
    def sumOfPower(self, nums: List[int], k: int) -> int:
        MOD = 1_000_000_007
        n = len(nums)
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        
        dp[0][0] = 1

        for i in range(1, n + 1):
            for j in range(0, k + 1):
                if j >= nums[i - 1]:
                    dp[i][j] = (dp[i - 1][j] * 2 + dp[i - 1][j - nums[i - 1]]) % MOD
                else:
                    dp[i][j] = (dp[i - 1][j] * 2) % MOD

        return dp[n][k]

if __name__ == '__main__':
    print(Solution().sumOfPower([1, 2, 3], 3))


"""

使用一维数组化简

"""
class Solution:
    def sumOfPower(self, nums: List[int], k: int) -> int:
        MOD = 1_000_000_007
        dp = [1] + [0] * k

        for x in nums:
            for j in range(k, -1, -1):
                dp[j] = (dp[j] * 2 + (dp[j - x] if j >= x else 0)) % MOD
        
        return dp[k]

if __name__ == '__main__':
    print(Solution().sumOfPower([1, 2, 3], 3))