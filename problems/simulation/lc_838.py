class Solution:
    def pushDominoes(self, dominoes: str) -> str:
        s = list("L" + dominoes + "R")  # 前后各加一个哨兵
        pre = 0  # 上一个 L 或 R 的位置
        for i, ch in enumerate(s):
            if ch == ".":
                continue
            if ch == s[pre]:  # L...L 或 R...R
                s[pre + 1 : i] = ch * (i - pre - 1)  # 全变成 s[i]
            elif ch == "L":  # R...L
                m = (pre + i - 1) // 2
                s[pre + 1 : m + 1] = "R" * (m - pre)  # 前一半变 R
                m = (pre + i) // 2 + 1
                s[m:i] = "L" * (i - m)  # 后一半变 L
            pre = i
        return "".join(s[1:-1])  # 去掉前后哨兵
