#! /usr/bin/python3
while True: # 多组数据
    try:
        n, m = map(int, input().split())
        print(n, m)
    except EOFError:
        break