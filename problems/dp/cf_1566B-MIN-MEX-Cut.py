t = int(input())
for test in range(t):
    s = input()
    zeros = s.count('0')
    if zeros == 0:
        print(0)
        continue

    first = s.find('0')
    last = s.rfind('0')

    if last - first + 1 == zeros:
        print(1)
    else:
        print(2)