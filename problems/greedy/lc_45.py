from typing import List


"""
https://leetcode.cn/problems/jump-game-ii/?envType=daily-question&envId=2025-01-27
"""


class Solution:
    def jump(self, nums: List[int]) -> int:
        ans = 0
        curr_right = 0
        next_right = 0
        n = len(nums)
        for i in range(n - 1):
            next_right = max(next_right, i + nums[i])
            if i == curr_right:
                curr_right = next_right
                ans += 1
        return ans
