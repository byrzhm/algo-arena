#include <bits/stdc++.h>

constexpr auto MAX = 100005;
std::array<int, MAX> expect; // size=n
std::array<int, MAX> time0;  // size=m
int64_t A, B, C;
int n, m;

auto
unhappy_teacher(int mintime) -> int64_t
{
    int64_t less = 0, more = 0;
    for (int i = 0; i < m; i++) {
        if (time0[i] > mintime) {
            less += time0[i] - mintime;
        } else {
            more += mintime - time0[i];
        }
    }

    return (A < B ?
          std::min(less, more) * A + (less - std::min(less, more)) * B
        : less * B);
}

auto
unhappy_student(int mintime) -> int64_t
{
    int64_t unhappy = 0;
    for (int i = 0; i < n; i++)
        if (expect[i] < mintime)
            unhappy += static_cast<int64_t>((mintime - expect[i]) * C);

    return unhappy;
}

auto
main() -> int
{
    int64_t min_unhappy = INT64_MAX;
    int left {1}, right {100000};

    std::cin >> A >> B >> C
             >> n >> m;

    for (int i = 0; i < n; i++)
        std::cin >> expect[i];
    for (int i = 0; i < m; i++)
        std::cin >> time0[i];

    std::sort(expect.begin(), expect.begin() + n);
    std::sort(time0.begin(), time0.begin() + m);

    if (C >= 1e16) {
        std::cout << unhappy_teacher(expect[0]) << std::endl;
        return 0;
    }

    while (right - left >= 3) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        int64_t unhappy1 = unhappy_teacher(mid1) + unhappy_student(mid1);
        int64_t unhappy2 = unhappy_teacher(mid2) + unhappy_student(mid2);
        if (unhappy1 > unhappy2)
            left = mid1;
        else
            right = mid2;
    }

    for (int i = left; i <= right; i++) {
        int64_t unhappy = unhappy_teacher(i) + unhappy_student(i);
        // printf("mintime=%d, unhappy_teacher=%ld, unhappy_student=%ld\n",
        //      i, unhappy_teacher(i), unhappy_student(i));
        // printf("    unhappy=%ld\n", unhappy);
        min_unhappy = std::min(unhappy, min_unhappy);
    }

    std::cout << min_unhappy << std::endl;

    return 0;
}