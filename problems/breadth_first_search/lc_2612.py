from sortedcontainers import SortedList
from collections import deque
from typing import List

# fmt: off
class Solution:
    def minReverseOperations(self, n: int, p: int, banned: List[int], k: int) -> List[int]:
        ban = set(banned) | {p}
        indices = [SortedList(), SortedList()]  # import sortedcontainers
        for i in range(n):
            if i not in ban:
                indices[i % 2].add(i)
        indices[0].add(n)  # 哨兵，下面无需判断越界
        indices[1].add(n)

        ans = [-1] * n
        ans[p] = 0  # 起点
        q = deque([p])
        while q:
            i = q.popleft()
            # indices[mn % 2] 中的从 mn 到 mx 的所有下标都可以从 i 翻转到
            mn = max(i - k + 1, k - i - 1)
            mx = min(i + k - 1, n * 2 - k - i - 1)
            sl = indices[mn % 2]
            idx = sl.bisect_left(mn)
            while sl[idx] <= mx:
                j = sl.pop(idx)  # 注意 pop(idx) 会使后续元素向左移，不需要写 idx += 1
                ans[j] = ans[i] + 1  # 移动一步
                q.append(j)
        return ans
# fmt: on
