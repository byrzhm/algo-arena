g = [[0] * 5 for _ in range(5)]

def gameover():
    s = 0
    for i in range(5):
        s = sum(g[i])
        if s == 0 or s == 5:
            return True

    for j in range(5):
        s = 0
        for i in range(5):
            s += g[i][j]
        if s == 0 or s == 5:
            return True

    s = 0
    for i in range(5):
        s += g[i][i]

    if s == 0 or s == 5:
        return True

    s = 0
    for i in range(5):
        s += g[i][-i]

    if s == 0 or s == 5:
        return True

    return False
    
def getPos(x):
    return x // 5, x % 5

ans = 0

def dfs(step, start):
    global ans
    if step == 13:
        if not gameover():
            ans += 1
        return

    for idx in range(start, 13 + step):
        i, j = getPos(idx)
        g[i][j] = 1
        dfs(step + 1, idx + 1)
        g[i][j] = 0

dfs(0, 0)
print(ans)

