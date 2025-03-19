from typing import List
from collections import Counter


# brute-force
class Solution:
    def findMatrix(self, nums: List[int]) -> List[List[int]]:
        ans: List[List[int]] = [[]]
        for x in nums:
            flag = True
            for row in ans:
                if x not in row:
                    row.append(x)
                    flag = False
                    break
            if flag:
                ans.append([x])
        return ans


class Solution:
    def findMatrix(self, nums: List[int]) -> List[List[int]]:
        ans = []
        cnt = Counter(nums)
        while cnt:
            row = list(cnt)
            ans.append(row)
            for x in row:
                cnt[x] -= 1
                if cnt[x] == 0:
                    del cnt[x]
        return ans
