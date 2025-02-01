from typing import List


class Solution:
    def search(self, nums: List[int], target: int) -> bool:
        tbl = set()
        for x in nums:
            tbl.add(x)
        return target in tbl


class Solution:
    def search(self, nums: List[int], target: int) -> bool:
        return target in nums


"""
作者：灵茶山艾府
链接：https://leetcode.cn/problems/search-in-rotated-sorted-array-ii/solutions/3058425/ji-yu-33-ti-de-jian-ji-xie-fa-zhi-xu-zen-uayi/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
"""


class Solution:
    def search(self, nums: List[int], target: int) -> int:
        def check(i: int) -> bool:
            x = nums[i]
            if x > nums[right]:
                return target > nums[right] and x >= target
            return target > nums[right] or x >= target

        left, right = -1, len(nums) - 1  # 开区间 (-1, n-1)
        while left + 1 < right:  # 开区间不为空
            mid = (left + right) // 2
            if nums[mid] == nums[right]:
                right -= 1
            elif check(mid):
                right = mid
            else:
                left = mid
        return nums[right] == target
