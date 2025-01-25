from typing import List
from itertools import permutations


# brute force: O(n!)
class Solution:
    def minimumMoney(self, transactions: List[List[int]]) -> int:
        n = len(transactions)
        ans = 0
        for permutation in permutations(range(n)):
            x = 0
            # ans_c = 0
            for idx in permutation:
                x += transactions[idx][0]
                ans = max(x, ans)
                # ans_c = max(x, ans_c)
                x -= transactions[idx][1]
            # print(f"{permutation}: {ans_c}")
        return ans


transactions = [[2, 1], [5, 0], [4, 2]]
print(Solution().minimumMoney(transactions))


"""
Hint 1:
  Split transactions that have cashback greater or equal to cost apart from
  transactions that have cashback less than cost. You will always earn money
  in the first scenario.

Hint 2:
  For transactions that have cashback greater or equal to cost, sort them by
  cost in descending order.

Hint 3:
  For transactions that have cashback less than cost, sort them by cashback in
  ascending order.

  c (x1, y1), (x2, y2)   x1 > y1, x2 > y2
                         y2 >= y1           => x2 > y2 >= y1
  c - x1 <-
  c - x1 + y1
  c - x1 + y1 - x2 <- 
  c - x1 + y1 - x2 + y2
"""


class Solution:
    def minimumMoney(self, transactions: List[List[int]]) -> int:
        for t in transactions:
            cost, cashback = t
            t.append(
                -1_000_000_001 + cashback if cost > cashback else 1_000_000_001 - cost
            )
        transactions.sort(key=lambda t: t[-1])
        ans = 0
        x = 0
        idx = 0
        for cost, cashback, flag in transactions:
            if flag > 0:
                break
            x += cost
            ans = x
            x -= cashback
            idx += 1
        if idx < len(transactions):  # 最后一笔是盈利项目
            ans = max(ans, x + transactions[idx][0])
        return ans


transactions = [[6, 5], [0, 5], [8, 5], [3, 6], [9, 0], [10, 1], [4, 10]]
print(Solution().minimumMoney(transactions))


"""
可以对上述的过程进行优化, 见官方题解
"""


class Solution:
    def minimumMoney(self, transactions: List[List[int]]) -> int:
        total_lose = 0
        res = 0
        for cost, cashback in transactions:
            total_lose += max(cost - cashback, 0)
            res = max(res, min(cost, cashback))
        return total_lose + res
