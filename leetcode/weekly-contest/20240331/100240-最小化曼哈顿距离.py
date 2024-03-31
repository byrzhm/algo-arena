from typing import List
from sortedcontainers import SortedList

class Solution:
    def minimumDistance(self, points: List[List[int]]) -> int:
        n = len(points)
        save = [[0, 0] for i in range(n)]
        for i, point in enumerate(points):
            save[i][0] = point[0] + point[1]
            save[i][1] = point[0] - point[1]

        sum_, diff_ = SortedList(), SortedList()
        for i in range(n):
            sum_.add(save[i][0])
            diff_.add(save[i][1])

        ret = 1e9
        for i in range(n):
            sum_.remove(save[i][0])
            diff_.remove(save[i][1])
            dist = max(sum_[-1] - sum_[0], diff_[-1] - diff_[0])
            ret = min(ret, dist)
            sum_.add(save[i][0])
            diff_.add(save[i][1])
            
        return ret