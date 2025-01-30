from typing import List
from collections import defaultdict

"""
Follow up:

- What if the given array is already sorted? How would you optimize your algorithm?
- What if nums1's size is small compared to nums2's size? Which algorithm is better?
- What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?
"""


class Solution:
    def intersect(self, nums1: List[int], nums2: List[int]) -> List[int]:
        n1, n2 = len(nums1), len(nums2)
        mp1 = defaultdict(int)
        ans = []

        if n1 > n2:  # 保证 nums1 是短的那个
            n1, n2 = n2, n1
            nums1, nums2 = nums2, nums1

        for x in nums1:
            mp1[x] += 1

        for y in nums2:
            if y in mp1:
                mp1[y] -= 1
                if mp1[y] >= 0:
                    ans.append(y)

        return ans
