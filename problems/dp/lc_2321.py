from typing import List


class Solution:
    def maximumsSplicedArray(self, nums1: List[int], nums2: List[int]) -> int:
        s1, s2 = sum(nums1), sum(nums2)
        diff = [x1 - x2 for x1, x2 in zip(nums1, nums2)]
        f_min, f_max = 0, 0
        min_s, max_s = 0, 0
        for x in diff:
            f_min = min(0, f_min) + x
            f_max = max(0, f_max) + x
            min_s = min(min_s, f_min)
            max_s = max(max_s, f_max)
        return max(s1 - min_s, s2 + max_s)
