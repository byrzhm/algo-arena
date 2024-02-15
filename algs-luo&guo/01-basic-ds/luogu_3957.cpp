// 单调队列优化DP
#include <bits/stdc++.h>

/// x[i] 表示起点到第 i 个格子的距离
/// s[i] 表示第 i 个格子的分数
int x[500005], s[500005];

int
main()
{
    /// n: 格子的数目
    /// d: 改进前机器人弹跳的固定距离
    /// k: 希望至少获得的分数
    /// g: 花 g 个金币改进他的机器人
    int n, d, k, g;

    std::cin >> n >> d >> k;
    for (int i = 0; i < n; i++)
        std::cin >> x[i] >> s[i];
}