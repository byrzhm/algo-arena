from typing import List


class Solution:
    def sortTheStudents(self, score: List[List[int]], k: int) -> List[List[int]]:
        score.sort(key=lambda x: x[k], reverse=True)
        return score


# fmt: off
score = [
    [10, 6,  9,  1],
    [ 7, 5, 11,  2],
    [ 4, 8,  3, 15]
]
k = 2

assert Solution().sortTheStudents(score, k) == [
    [ 7, 5, 11,  2],
    [10, 6,  9,  1],
    [ 4, 8,  3, 15],
]
# fmt: on
