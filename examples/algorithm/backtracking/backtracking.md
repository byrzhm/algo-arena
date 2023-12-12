# Backtracking Algorithm 模板

- 递归

```cpp
void backtracking(int step) {
    if (step == n) {
        // do something
        return;
    }
    for (int i = 0; i < n; i++) {
        if (check(step, i)) {
            // do something
            backtracking(step + 1);
            // do something
        }
    }
}
```

- 迭代

```cpp
void backtracking() {
    int step = 0;
    while (step >= 0) {
        if (step == n) {
            // do something
            step--;
        } else {
            for (int i = 0; i < n; i++) {
                if (check(step, i)) {
                    // do something
                    step++;
                    break;
                }
            }
        }
    }
}
```

## Online Judge

- [LeetCode](https://leetcode.cn/problemset/?topicSlugs=backtracking)
- [Codeforces](https://codeforces.com/problemset/tags/backtracking)
- [GeeksforGeeks](https://www.geeksforgeeks.org/backtracking-algorithms/)
