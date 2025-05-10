from typing import List
from math import inf


class Solution:
    def minSum(self, nums1: List[int], nums2: List[int]) -> int:
        sum1 = sum(nums1)
        sum2 = sum(nums2)
        zero1 = nums1.count(0)
        zero2 = nums2.count(0)

        if zero1 == 0:
            lb1, ub1 = sum1, sum1
        else:
            lb1, ub1 = sum1 + zero1, inf
        if zero2 == 0:
            lb2, ub2 = sum2, sum2
        else:
            lb2, ub2 = sum2 + zero2, inf

        # [lb1, ub1] 与 [lb2, ub2] 区间是否重叠
        if not (ub1 < lb2 or ub2 < lb1):
            return lb1 if lb1 > lb2 else lb2

        return -1


nums1 = [3, 2, 0, 1, 0]
nums2 = [6, 5, 0]
print(Solution().minSum(nums1, nums2))
