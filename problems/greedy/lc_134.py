from typing import List
from collections import deque


class Solution:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        n = len(gas)
        i = 0
        while i < n:
            sumOfGas = sumOfCost = 0
            cnt = 0
            while cnt < n:
                j = (i + cnt) % n
                sumOfGas += gas[j]
                sumOfCost += cost[j]
                if sumOfCost > sumOfGas:
                    break
                cnt += 1
            if cnt == n:
                return i
            else:
                i += cnt + 1
        return -1


class Solution:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        if sum(gas) < sum(cost):
            return -1

        res, total = 0, 0
        for i in range(len(gas)):
            total += gas[i] - cost[i]
            if total < 0:
                total = 0
                res = i + 1
        return res


gas = [1, 2, 3, 4, 5]
cost = [3, 4, 5, 1, 2]


def simulate(gas: List[int], cost: List[int]):
    n = len(gas)
    for start in range(n):
        now = 0
        print(f"start at {start}: {now} => +{gas[start]} -{cost[start]}")
        now += gas[start] - cost[start]
        for i in range(1, n + 1):
            print(
                f"\tArrival at {(start + i) % n}: {now} => +{gas[(start + i) % n]} -{cost[(start + i) % n]}"
            )
            now += gas[(start + i) % n] - cost[(start + i) % n]


simulate(gas, cost)
