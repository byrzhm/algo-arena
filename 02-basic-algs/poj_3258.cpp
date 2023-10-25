#include <algorithm>
#include <iostream>

#define int64_t long long

#define MAXN 50002
int n, m;
int64_t pos[MAXN];

bool checkmid(int64_t dist)
{
    int move = 0;
    int curr = 1, prev = 0;
    while (curr <= n) {
        if (pos[curr] - pos[prev] < dist) {
            move++;
            curr++;
        } else {
            prev = curr;
            curr++;
        }
    }

    return move <= m;
}

int main()
{
    int64_t l;
    std::cin >> l >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> pos[i];

    pos[++n] = l;
    std::sort(pos, pos + n);
    
    int64_t left = 0, right = l;
    while (left < right) {
        int64_t mid = left + ((right - left + 1) >> 1);
        if (checkmid(mid))
            left = mid;
        else
            right = mid - 1;
    }

    std::cout << left << std::endl;
    return 0;
}