#include <bits/stdc++.h>

constexpr auto MAX = 200005;
struct Range
{
    int id, start, end;
    bool operator<(const Range& other) const {
        return this->start < other.start;
    }
};

int n, m;
int n2;
std::array<Range, MAX * 2> w;
// go[s][i] 的意思是 s 为起点, 走过 2^i 个最优区间, 到达的区间
std::array<std::array<int, 20>, MAX> go; 
std::array<int, MAX> result;

void
getgo()
{
    int next = 0;
    for (int i = 0; i < n2; i++) {
        // 每名边防战士的奔袭区间都不会被其他边防战士的奔袭区间所包含
        // 每个区间的下一个是右端点最大的区间
        while (next < n2 && w[next].start <= w[i].end)
            next++;
        go[i][0] = next - 1; // 区间 i 的下一个区间
                             // next 不回头
    }

    // 倍增 : i = 1, 2, 3, ..., floor(log2(n))
    //       考虑最多跳过 n 个最优区间
    for (int i = 1; (1 << i) <= n; ++i) { 
        for (int s = 0; s < n2; s++)
            go[s][i] = go[go[s][i-1]][i-1];
    }
}

/// 从第 x 个战士出发
void
getans(int x)
{
    int len = w[x].start + m;
    int cur = x;
    int ans = 1;
    // 从最大的 i 开始找: 2^i = MAX
    for (int i = log2(MAX); i >= 0; i--) { 
        int pos = go[cur][i];
        if (pos && w[pos].end < len) {
            ans += 1 << i;
            cur = pos;
        }
    }
    result[w[x].id] = ans + 1;
}

int
main()
{
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        w[i].id = i;
        std::cin >> w[i].start >> w[i].end;
        if (w[i].start > w[i].end)
            w[i].end += m;
    }

    std::sort(w.begin(), w.begin() + n);
    
    n2 = n;
    for (int i = 0; i < n; i++) {
        w[n2].id = w[i].id;
        w[n2].start = w[i].start + m;
        w[n2].end = w[i].end + m;
        ++n2;
    }

    getgo();

    for (int i = 0; i < n; i++)
        getans(i);
    
    for (int i = 0; i < n; i++)
        std::cout << result[i] << (i == n - 1 ? '\n' : ' ');

    return 0;
}