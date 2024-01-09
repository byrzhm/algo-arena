# Backtracking Algorithm 模板

回溯法又称<font color=red>通用解题法</font>，是一种基于 DFS 的搜索算法，用于在一个庞大的搜索空间中寻找问题的解。回溯法的基本思想是：从问题的某一种状态（初始状态）出发，搜索从这种状态出发所能达到的所有“状态”，当一条路走到“尽头”的时候（不能再前进），再后退一步或若干步，从另一种可能“状态”出发，继续搜索，直到所有的“路径”（状态）都试探过。这种不断“前进”、不断“回溯”寻找解的方法，就称作“回溯法”。

在回溯过程中通常采用两种策略来避免无效搜索：

1. 用<font color=red>约束条件</font>来减去得不到可行解的子树；
2. 用<font color=red>目标函数</font>来减去得不到最优解的子树。

这两类函数统称为<font color=red>剪枝函数(Pruning Function)</font>。

## 递归回溯

```cpp
void backtracking(int step) {
    if (step == n) {
        // do something and return
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

## 迭代回溯

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

## 子集树算法框架

当所给的问题是从n个元素的集合S中找出满足某种性质的子集时, 相应的解空间树称为子集树。

```cpp
void backtracking(int step) {
    if (step == n) {
        // do something and return
        return;
    }
    for (int i = 0; i < 2; i++) {
        x[step] = i;
        if (check(step)) {
            backtracking(step + 1);
        }
    }
}
```

## 排列树算法框架

当所给的问题是从n个元素的集合S中找出满足某种性质的排列时, 相应的解空间树称为排列树。

```cpp
void backtracking(int step) {
    if (step == n) {
        // do something and return
        return;
    }
    for (int i = 0; i < n; i++) {
        std::swap(x[step], x[i]);
        if (check(step, i)) {
            backtracking(step + 1);
        }
        std::swap(x[step], x[i]);
    }
}
```

## 例题

### 枚举全排列

给定一个正整数n，输出1~n的全排列。

```cpp
template <typename T>
void perm(T list[], int k, int m) {
    if (k == m) {
        for (int i = 0; i <= m; i++) {
            std::cout << list[i] << " ";
        }
        std::cout << std::endl;
    } else {
        for (int i = k; i <= m; i++) {
            std::swap(list[k], list[i]);
            perm(list, k + 1, m);
            std::swap(list[k], list[i]);
        }
    }
}
```

### 装载问题

有n个集装箱要装上两艘载重量分别为c1和c2的轮船，其中集装箱i的重量为wi，且全部集装箱重量不超过两艘轮船的载重量之和。设计一个算法，找出一种装载方案。

```cpp
#include <bits/stdc++.h>
int n;         ///< 集装箱数量
int c1;        ///< 第一艘轮船的载重量
int c2;        ///< 第二艘轮船的载重量
int w[100];    ///< 集装箱重量
int x[100];    ///< 当前解
int bestw = 0; ///< 当前最优解
int cw = 0;    ///< 当前载重量
int r = 0;     ///< 剩余集装箱重量

void init() {
    std::cin >> n >> c1 >> c2;
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
        r += w[i];
    }
}

void backtracking(int step) { // step表示当前处理第几个集装箱
    if (step == n) { // 递归边界, 表示已经处理完所有集装箱
        // if (cw > bestw) { // 不是最优解的被剪枝了, 所以不需要判断
        bestw = cw; // 更新最优解
        // }
        return;
    }
    r -= w[step]; // 选择集装箱
    if (cw + w[step] <= c1) {
        x[step] = 1; // x[step] = 1, 表示装入第一艘轮船
        cw += w[step]; // 更新当前载重量
        backtracking(step + 1); // 递归回溯
        cw -= w[step]; // 撤销选择
    }
    if (cw + r > bestw) { // cw + r > bestw, 表示有可能找到更优解
        x[step] = 0; // x[step] = 0, 表示装入第二艘轮船
        backtracking(step + 1); // 递归回溯
    }
    r += w[step]; // 撤销选择
}

int main() {
    init();
    backtracking(0);
    std::cout << bestw << std::endl;
    return 0;
}
```

### 0-1背包问题

有n件物品和一个容量为c的背包。第i件物品的重量是wi，价值是vi，求解将哪些物品装入背包可使价值总和最大。

```cpp
#include <bits/stdc++.h>
int n;         ///< 物品数量
int c;         ///< 背包容量
int w[100];    ///< 物品重量
int v[100];    ///< 物品价值
int bestv = 0; ///< 当前最优解
int cw = 0;    ///< 当前载重量
int cv = 0;    ///< 当前价值

int bound(int step) { // 计算上界
    int cleft = c - cw; // 剩余背包容量
    int b = cv; // 上界

    // !!! 以物品单位重量价值递减顺序装入物品 !!!
    while (step < n && w[step] <= cleft) {
        cleft -= w[step];
        b += v[step];
        step++;
    }
    if (step < n) { // 装满背包
        b += v[step] * cleft / w[step];
    }
    return b;
}

void backtracking(int step) { // step表示当前处理第几个物品
    if (step == n) { // 递归边界, 表示已经处理完所有物品
        bestv = cv; // 更新最优解
        return;
    }

    if (cw + w[step] <= c) {
        cw += w[step]; // 更新当前载重量
        cv += v[step]; // 更新当前价值
        backtracking(step + 1); // 递归回溯
        cw -= w[step]; // 撤销选择
        cv -= v[step]; // 撤销选择
    }

    // bound(step + 1) > bestv, 表示有可能找到更优解
    if (bound(step + 1) > bestv) { 
        backtracking(step + 1); // 递归回溯
    }
}
```

### 批处理作业调度问题

给定n个作业的集合$\{J_1, J_2, ..., J_n\}$。每个作业必须先由机器1处理, 然后再由机器2处理。作业$J_i$在机器j上的处理时间为$t_{ji}$。对于一个确定的作业调度, 设$F_{ji}$是作业i在机器j上完成处理的时间。所有作业在机器2上完成处理的时间和称为该作业调度的完成时间。设计一个算法, 对给定的n个作业的集合, 求出完成时间最短的作业调度。

```cpp
#include <bits/stdc++.h>
void Backtracking(int step) {
    if (step == n_) {
        bestx_ = x_;
        bestf_ = f_;
        return;
    }

    int prev_f2 = (step > 0) ? f2_[step - 1] : 0; // 机器2处理完前一个作业的完成处理时间
    for (int i = step; i < n_; i++) {
            f1_ += time_[x_[i]][0]; // 机器1处理完第i个作业的完成处理时间
            f2_[step] = ((prev_f2 > f1_) ? prev_f2 : f1_) + time_[x_[i]][1]; // 机器2处理完第i个作业的完成处理时间
            f_ += f2_[step]; // 完成时间和
        if (f_ < bestf_) { // 剪枝
            std::swap(x_[step], x_[i]); // 交换
            Backtracking(step + 1);
            std::swap(x_[step], x_[i]); // 回溯
        }
            // 回溯
            f1_ -= time_[x_[i]][0]; 
            f_ -= f2_[step];
    }
}
```

### m图着色问题

给定一个无向图G，用最少的颜色对图G的顶点着色，使得任意两个相邻的顶点颜色不同。设计一个算法，找出一种着色方案。

```cpp
#include <bits/stdc++.h>

void Backtracking(int step) {
    if (step == n_) {
        if (sum_ == 0) {
            bestx_ = x_;
        }
        sum_++;
        return;
    }

    for (int i = 1; i <= m_; i++) {
        x_[step] = i;
        if (Check(step)) {
            Backtracking(step + 1);
        }
    }
}

bool Check(int step) {
    for (int i = 0; i < step; i++) {
        if ((graph_[i][step] != 0) && x_[i] == x_[step]) {
            return false;
        }
    }
    return true;
}
```

### n皇后问题

在n×n的棋盘上放置n个皇后，使得它们不能互相攻击，即任意两个皇后都不能处于同一行、同一列或同一斜线上。设计一个算法，找出一种放置方案。

```cpp
#include <bits/stdc++.h>
void Backtracking(int step) {
    if (step == positions_.size()) {
        AppendSln();
    } else {
        for (int i = 0; i < n_; i++) {
            positions_[step] = i;
            if (IsValid(step)) {
                Backtracking(step + 1);
            }
        }
    }
}

bool IsValid(int step) {
    for (int i = 0; i < step; i++) {
        if (positions_[step] == positions_[i] || std::abs(step - i) == std::abs(positions_[step] - positions_[i])) {
            return false;
        }
    }
    return true;
}
```

### 旅行售货员问题

有n个城市，它们之间的距离用一个n×n的矩阵D表示，其中Di,j表示从城市i到城市j的距离。旅行售货员从某个城市出发，必须经过每个城市且只能经过一次，最后回到出发城市。设计一个算法，找出一条最短的路径。

```cpp
#include <bits/stdc++.h>
void Backtracking(int step) {
    if (step == n_ - 1) { /* 已经搜索到叶节点, 已经选择了最后一个城市 */
        if (graph_[current_path_[n_ - 1]][current_path_[n_ - 2]] != INF && graph_[current_path_[n_ - 1]][0] != INF) {
            if (current_weight_ + graph_[current_path_[n_ - 1]][current_path_[n_ - 2]] + graph_[current_path_[n_ - 1]][0] <
                best_weight_) { /* 当前回路更优, 更新最优搜索结果 */
                best_weight_ =
                    current_weight_ + graph_[current_path_[n_ - 2]][current_path_[n_ - 1]] + graph_[current_path_[n_ - 1]][0];
                best_path_ = current_path_;
            }
        }

    } else { /* 如果搜索没有到叶节点, 当前得到的部分路径
                <0, current_path_[1], ..., current_path_[step - 1], ?, ..., ?>*/
        for (int i = step; i < n_; i++) {
            if (graph_[current_path_[step - 1]][current_path_[i]] != INF &&
                current_weight_ + graph_[current_path_[step - 1]][current_path_[i]] < best_weight_) {
                std::swap(current_path_[step], current_path_[i]); /* 加入第i个城市 */
                current_weight_ =
                    current_weight_ + graph_[current_path_[step - 1]][current_path_[step]]; /* 更新扩展之后的路径代价 */
                Backtracking(step + 1); /* 递归搜索以 current_path_[i] 为根的后续子树 */
                current_weight_ = current_weight_ - graph_[current_path_[step - 1]][current_path_[step]]; /* 回溯 */
                std::swap(current_path_[step], current_path_[i]);
            }
        }
    }
}
```

## Online Resources

- [LeetCode](https://leetcode.cn/problemset/?topicSlugs=backtracking)
- [Codeforces](https://codeforces.com/problemset/tags/backtracking)
- [GeeksforGeeks](https://www.geeksforgeeks.org/backtracking-algorithms/)
