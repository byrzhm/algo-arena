from cmath import inf
from itertools import accumulate
from typing import List

# class Solution:
#     def minimumMoves(self, nums: List[int], k: int, maxChanges: int) -> int:
#         acc = list(accumulate(nums, initial=0))
#         n = len(nums)
#         pos_sum = list(accumulate((i if nums[i] else 0 for i in range(n)), initial=0))
        
#         result = inf
#         for i in range(n):
#             ans = 0
#             tmp = k

#             # 将 i - 1, i, i + 1 的 1 用掉
#             for p in range(i - 1, i + 2):
#                 if 0 <= p < n and nums[p] and tmp:
#                     tmp -= 1
#                     ans += abs(p - i) # 在 i - 1, i + 1 时要进行移动操作

#             if maxChanges >= tmp: # maxChanges 够用
#                 ans += tmp * 2    # 赋值 tmp 次在旁边，然后移动到 index 有 tmp 次，总共 2 * tmp 次
#             else:                 # 把临近的和 maxChanges 都用掉还不够
#                 ans = 2 * maxChanges
#                 tmp = k - maxChanges

#                 l, r = 0, n
#                 while l <= r:
#                     m = (l + r) // 2
#                     # 以 i 为中心 m 为半径，正好有 tmp 以上的 1
#                     if acc[min(n, i + m + 1)] - acc[max(0, i - m)] >= tmp:
#                         r = m - 1
#                     else:
#                         l = m + 1
#                 m = l

#                 # i 右侧的 1
#                 ans += (pos_sum[min(n, i+m+1)] - pos_sum[i]) - (acc[min(n, i+m+1)] - acc[i]) * i
#                 # i 左侧的 1
#                 ans += -(pos_sum[i+1] - pos_sum[max(0, i-m)]) + (acc[i+1] - acc[max(0, i-m)]) * i

#                 # 注意这样选取区间，区间元素个数可能比需要的多一个，那个元素需要去除
#                 if acc[min(n, i + m + 1)] - acc[max(0, i - m)] > tmp:
#                     ans -= m

#             # 更新 result
#             result = min(ans, result)

#         return result


class Solution:
    def minimumMoves(self, nums: List[int], k: int, maxChanges: int) -> int:
        pos = []
        c = 0
        n = len(nums)
        for i in range(n):
            if nums[i]:
                pos.append(i)
                c = max(c, 1)
                if i + 1 < n and nums[i + 1]:
                    if i + 2 < n and nums[i + 2]:
                        c = 3
                    else:
                        c = max(c, 2)

        c = min(k, c) # k - c >= 0
        if maxChanges >= k - c:
            # c = 0 -> 0, c = 1 -> 0, c = 2 -> 1, c = 3 -> 2
            return max(c - 1, 0) + (k - c) * 2

        ans = inf
        n = len(pos)
        size = k - maxChanges
        prefix = list(accumulate(pos, initial=0))

        for right in range(size, n + 1):
            #  s1+s2 是 j 在 [left, right) 中的所有 pos[j] 到 pos[(left+right)/2] 的距离之和
            left = right - size
            mid = left + size // 2
            tmp = pos[mid] * (mid - left) - (prefix[mid] - prefix[left])
            tmp += prefix[right] - prefix[mid] - pos[mid] * (right - mid)
            ans = min(ans, tmp)

        return ans + 2 * maxChanges

                        