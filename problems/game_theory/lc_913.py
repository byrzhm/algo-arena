from typing import List
from collections import deque

"""
## 博弈知识介绍

这道题是博弈问题，猫和老鼠都按照最优策略参与游戏。

在阐述具体解法之前，首先介绍博弈问题中的三个概念：必胜状态、必败状态与必和状态。

1. 对于特定状态，如果游戏已经结束，则根据结束时的状态决定必胜状态、必败状态与必和状态。
  - 如果分出胜负，则该特定状态对于获胜方为必胜状态，对于落败方为必败状态。
  - 如果是平局，则该特定状态对于双方都为必和状态。
2. 从特定状态开始，如果存在一种操作将状态变成必败状态，则当前玩家可以选择该操作，将必败状态留给对方玩家，因此该特定状态对于当前玩家为必胜状态。
3. 从特定状态开始，如果所有操作都会将状态变成必胜状态，则无论当前玩家选择哪种操作，都会将必胜状态留给对方玩家，因此该特定状态对于当前玩家为必败状态。
4. 从特定状态开始，如果任何操作都不能将状态变成必败状态，但是存在一种操作将状态变成必和状态，则当前玩家可以选择该操作，将必和状态留给对方玩家，因此该特定状态对于双方玩家都为必和状态。

对于每个玩家，最优策略如下：
1. 争取将必胜状态留给自己，将必败状态留给对方玩家。
2. 在自己无法到达必胜状态的情况下，争取将必和状态留给自己。
"""

DRAW = 0
MOUSE_WIN = 1
CAT_WIN = 2


# DP: O(n^5)
class Solution:
    def catMouseGame(self, graph: List[List[int]]) -> int:
        n = len(graph)
        dp = [[[-1] * (2 * n * (n - 1)) for _ in range(n)] for _ in range(n)]

        def getResult(mouse: int, cat: int, turns: int) -> int:
            if turns == 2 * n * (n - 1):
                return DRAW
            res = dp[mouse][cat][turns]
            if res != -1:
                return res
            if mouse == 0:
                res = MOUSE_WIN
            elif mouse == cat:
                res = CAT_WIN
            else:
                res = getNextResult(mouse, cat, turns)
            dp[mouse][cat][turns] = res
            return res

        def getNextResult(mouse: int, cat: int, turns: int) -> int:
            curMove = mouse if turns % 2 == 0 else cat
            defaultRes = MOUSE_WIN if curMove != mouse else CAT_WIN
            res = defaultRes
            for next in graph[curMove]:
                if curMove == cat and next == 0:  # 猫不能去节点 0
                    continue
                nextMouse = next if curMove == mouse else mouse
                nextCat = next if curMove == cat else cat
                nextRes = getResult(nextMouse, nextCat, turns + 1)
                if nextRes != defaultRes:
                    res = nextRes
                    if res != DRAW:
                        break
            return res

        return getResult(1, 2, 0)


# Topological Sort: O(n^3)

MOUSE_TURN = 0
CAT_TURN = 1

DRAW = 0
MOUSE_WIN = 1
CAT_WIN = 2


class Solution:
    def catMouseGame(self, graph: List[List[int]]) -> int:
        n = len(graph)
        degrees = [[[0, 0] for _ in range(n)] for _ in range(n)]
        results = [[[0, 0] for _ in range(n)] for _ in range(n)]
        for i in range(n):
            for j in range(1, n):
                degrees[i][j][MOUSE_TURN] = len(graph[i])
                degrees[i][j][CAT_TURN] = len(graph[j])
        for y in graph[0]:
            for i in range(n):
                degrees[i][y][CAT_TURN] -= 1

        q = deque()
        for j in range(1, n):
            results[0][j][MOUSE_TURN] = MOUSE_WIN
            results[0][j][CAT_TURN] = MOUSE_WIN
            q.append((0, j, MOUSE_TURN))
            q.append((0, j, CAT_TURN))
        for i in range(1, n):
            results[i][i][MOUSE_TURN] = CAT_WIN
            results[i][i][CAT_TURN] = CAT_WIN
            q.append((i, i, MOUSE_TURN))
            q.append((i, i, CAT_TURN))

        while q:
            mouse, cat, turn = q.popleft()
            result = results[mouse][cat][turn]
            if turn == MOUSE_TURN:
                prevStates = [(mouse, prev, CAT_TURN) for prev in graph[cat]]
            else:
                prevStates = [(prev, cat, MOUSE_TURN) for prev in graph[mouse]]
            for prevMouse, prevCat, prevTurn in prevStates:
                if prevCat == 0:
                    continue
                if results[prevMouse][prevCat][prevTurn] == DRAW:
                    canWin = (
                        result == MOUSE_WIN
                        and prevTurn == MOUSE_TURN
                        or result == CAT_WIN
                        and prevTurn == CAT_TURN
                    )
                    if canWin:
                        results[prevMouse][prevCat][prevTurn] = result
                        q.append((prevMouse, prevCat, prevTurn))
                    else:
                        degrees[prevMouse][prevCat][prevTurn] -= 1
                        if degrees[prevMouse][prevCat][prevTurn] == 0:
                            results[prevMouse][prevCat][prevTurn] = (
                                CAT_WIN if prevTurn == MOUSE_TURN else MOUSE_WIN
                            )
                            q.append((prevMouse, prevCat, prevTurn))
        return results[1][2][MOUSE_TURN]
