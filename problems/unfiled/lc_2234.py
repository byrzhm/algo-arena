from typing import List
import bisect


# fmt: off
class Solution:
    def maximumBeauty(self, flowers: List[int], newFlowers: int, target: int, full: int, partial: int) -> int:
        n = len(flowers)
        flowers.sort()
        idx = bisect.bisect_left(flowers, target)
        if idx == 0:
            return n * full
        
        left_flowers = newFlowers - (target * idx - sum(flowers[:idx]))
        if left_flowers >= 0:
            return max(n * full, (n - 1) * full + (target - 1) * partial)

        ans = pre_sum = j = 0
        # 枚举 i，表示后缀 [i, idx - 1] 种满（i=0 的情况上面已讨论）
        for i in range(1, idx + 1):
            # 撤销，flowers[i-1] 不变成 target
            left_flowers += target - flowers[i - 1]
            if left_flowers < 0:  # 花不能为负数，需要继续撤销
                continue

            # 满足以下条件说明 [0, j] 都可以种 flowers[j] 朵花
            while j < i and flowers[j] * j <= pre_sum + left_flowers:
                pre_sum += flowers[j]
                j += 1

            # 计算总美丽值
            # 在前缀 [0, j-1] 中均匀种花，这样最小值最大
            avg = (left_flowers + pre_sum) // j  # 由于上面特判了，这里 avg 一定小于 target
            total_beauty = avg * partial + (n - i) * full
            ans = max(ans, total_beauty)

        return ans

# fmt: on


flowers = [20, 1, 15, 17, 10, 2, 4, 16, 15, 11]
newFlowers = 2
target = 20
full = 10
partial = 2

print(Solution().maximumBeauty(flowers, newFlowers, target, full, partial))
