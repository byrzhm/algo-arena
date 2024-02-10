### 在python中处理eof输入

#### 每行一个整数, 行数若干

``` python
import sys
for n in sys.stdin:
    n = int(n)
    print(n, type(n))
```

#### 每行两个整数, 行数若干

``` python
while True: # 多组数据
    try:
        n, m = map(int, input().split())
        print(n, m)
    except EOFError:
        break
```