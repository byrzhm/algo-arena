from typing import List

class Solution:
    def firstDayBeenInAllRooms(self, nextVisit: List[int]) -> int:
        n = len(nextVisit)

        for i in range(n):
            assert 0 <= nextVisit[i] <= i

        cnt = [0] * n
        trace = []
        pos = 0
        while n - 1 not in trace:
            trace.append(pos)
            cnt[pos] += 1

            # 第一次到pos位置时，检查cnt之前是否为全为偶数
            if cnt[pos] == 1:
                print(cnt)

            if cnt[pos] % 2 == 0:
                pos = (pos + 1) % n
            else:
                pos = nextVisit[pos]
                
        print(trace)

Solution().firstDayBeenInAllRooms([0, 1, 1, 0, 2])


'''
    f[i] -> 第一次到i号所需要的时间，注意此时[0, i-1]房间访问次数都为偶数次
    step1: 第一次到i-1号: f[i-1]
    step2: 从i-1到next[i-1]: +1
    step3: 从next[i-1]到i-1: f[i-1] - f[next[i-1]]
    step4: 从i-1到i: +1
'''
class Solution:
    def firstDayBeenInAllRooms(self, nextVisit: List[int]) -> int:
        n = len(nextVisit)
        dp = [0] * n
        mod = 10 ** 9 + 7
        
        for i in range(1, n):
            dp[i] = (dp[i - 1] + 1 + dp[i - 1] - dp[nextVisit[i - 1]] + 1) % mod

        return dp[-1]

print(Solution().firstDayBeenInAllRooms([0, 1, 2]))
print(Solution().firstDayBeenInAllRooms([0, 0, 1, 0, 2]))
print(Solution().firstDayBeenInAllRooms([0, 1, 1, 0, 2]))