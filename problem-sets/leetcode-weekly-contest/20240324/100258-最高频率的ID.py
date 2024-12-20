"""
SortedList
https://grantjenks.com/docs/sortedcontainers/sortedlist.html
"""
from collections import Counter
from sortedcontainers import SortedList
from typing import List
from heapq import heappush, heappop

class Solution:
    def mostFrequentIDs(self, nums: List[int], freq: List[int]) -> List[int]:
        cnt = Counter()
        sl = SortedList()
        ans = []
        for x, f in zip(nums, freq):
            sl.discard(cnt[x])  # 多个 cnt[x] 只会移除一个
            cnt[x] += f
            sl.add(cnt[x])
            ans.append(sl[-1])
        return ans

"""

heap & lazy

"""

class Solution:
    def mostFrequentIDs(self, nums: List[int], freq: List[int]) -> List[int]:
        ans = []
        cnt = Counter()
        h = []
        for x, f in zip(nums, freq):
            cnt[x] += f
            heappush(h, (-cnt[x], x))  # 取负号变成最大堆
            while -h[0][0] != cnt[h[0][1]]:  # 堆顶保存的数据已经发生变化
                heappop(h)  # 删除
            ans.append(-h[0][0])
        return ans
