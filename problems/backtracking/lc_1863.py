from typing import List
from functools import reduce
from operator import or_


class Solution:
    def subsetXORSum(self, nums: List[int]) -> int:
        n = len(nums)
        ans = 0

        def backtrack(i: int, v_xor: int) -> None:
            nonlocal ans
            if i == n:
                ans += v_xor
                return

            x = nums[i]
            v_xor ^= x
            backtrack(i + 1, v_xor)
            v_xor ^= x
            backtrack(i + 1, v_xor)

        backtrack(0, 0)
        return ans


class Solution:
    def subsetXORSum(self, nums: List[int]) -> int:
        return reduce(or_, nums) << (len(nums) - 1)
