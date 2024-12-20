t = int(input())
for test in range(t):
    n = int(input())
    a = []
    for row in range(2):
        a.append([int(i) for i in input().split()])

    sum1, sum2 = 0, 0
    ans = int(2e9 + 10)
    for i in range(n): sum1 += a[0][i]
    for i in range(n):
        sum1 -= a[0][i]
        ans = min(ans, max(sum1, sum2))
        sum2 += a[1][i]

    print(ans)