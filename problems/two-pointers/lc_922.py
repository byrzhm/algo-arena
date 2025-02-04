from typing import List


class Solution:
    def sortArrayByParityII(self, nums: List[int]) -> List[int]:
        n, i0, i1 = len(nums), 0, 1
        while True:
            while i0 < n and nums[i0] % 2 == 0:
                i0 += 2
            if i0 >= n:
                break

            while i1 < n and nums[i1] % 2 == 1:
                i1 += 2
            # 后面一定有偶数, 所以 i1 < n 一定成立
            nums[i0], nums[i1] = nums[i1], nums[i0]
            i1 += 2

        return nums


class Solution:
    def sortArrayByParityII(self, nums: List[int]) -> List[int]:
        n = len(nums)
        i0, i1 = 0, 1
        while i0 < n:  # 梯田温泉写法
            if nums[i0] % 2 == 0:  # 找第一个奇数
                i0 += 2
            elif nums[i1] % 2 == 1:  # 找第一个偶数
                i1 += 2
            else:  # 都找到了就swap
                nums[i0], nums[i1] = nums[i1], nums[i0]
                i0 += 2
                i1 += 2
            # 以此往复，直至结束
            # 由于对半开，i0结束可以代表全部结束
        return nums
