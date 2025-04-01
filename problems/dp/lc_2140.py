from typing import List
from functools import cache


# O(2^N)
class Solution:
    def mostPoints(self, questions: List[List[int]]) -> int:
        n = len(questions)

        @cache
        def dfs(i: int, hold: bool) -> int:
            if i >= n:
                return 0
            points, brainpower = questions[i]
            if hold:
                return points + max(
                    dfs(i + brainpower + 1, True), dfs(i + brainpower + 1, False)
                )
            return max(dfs(i + 1, True), dfs(i + 1, False))

        # for i in range(n):
        #     print(f"dfs({i}, True)={dfs(i, True)}")
        #     print(f"dfs({i}, False)={dfs(i, False)}")

        return max(dfs(0, True), dfs(0, False))


class Solution:
    def mostPoints(self, questions: List[List[int]]) -> int:
        n = len(questions)

        @cache
        def dfs(i: int) -> int:
            if i >= n:
                return 0
            return max(dfs(i + 1), questions[i][0] + dfs(i + questions[i][1] + 1))

        return dfs(0)


questions = [[3, 2], [4, 3], [4, 4], [2, 5]]
print(Solution().mostPoints(questions))
