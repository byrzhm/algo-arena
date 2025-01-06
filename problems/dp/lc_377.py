from typing import List
from functools import cache
import unittest

class Solution1:
    def combinationSum4(self, nums: List[int], target: int) -> int:
        @cache
        def dfs(i: int):
            if i == 0:
                return 1
            return sum(dfs(i - x) for x in nums if x <= i)
        return dfs(target)

class Solution2:
    def combinationSum4(self, nums: List[int], target: int) -> int:
        dp = [1] + [0] * target
        for i in range(1, target + 1):
            dp[i] = sum(dp[i - x] for x in nums if x <= i)
        return dp[target]


class TestSolution1(unittest.TestCase):
    def test_1(self):
        sol = Solution1()
        nums = [1, 2, 3]
        target = 4
        self.assertEqual(sol.combinationSum4(nums, target), 7)

class TestSolution2(unittest.TestCase):
    def test_1(self):
        sol = Solution2()
        nums = [1, 2, 3]
        target = 4
        self.assertEqual(sol.combinationSum4(nums, target), 7)


if __name__ == "__main__":
    unittest.main()
