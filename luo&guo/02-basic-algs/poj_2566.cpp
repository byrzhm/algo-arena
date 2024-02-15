// i > j >= 0
// sumto[i] = a[0] + a[1] + ... + a[i]
// sumto[i] - sumto[j] = a[j+1] + a[j+2] + ... + a[i]
#include <cstdio>
#include <climits>
#include <algorithm>

struct Node {
    int index;
    int sumto;
} v[1000001];

bool operator<(const Node& l, const Node& r) {
    return l.sumto < r.sumto;
}

void
boundFind(int n, int t)
{
    int l, r, min;
    int left, right, sum;
    l = 0; r = 1;
    min = INT_MAX;
    while (r <= n) {
        int sub = v[r].sumto - v[l].sumto;
        if (abs(sub - t) < min) {
            min = abs(sub - t);
            left = std::min(v[l].index, v[r].index) + 1;
            right = std::max(v[l].index, v[r].index);
            sum = sub;
        }

        if (sub < t) r++;
        else if (sub > t) l++;
        else break;
        
        if (r == l) r++;
    }
    printf("%d %d %d\n", sum, left, right);
}

int
main()
{
    int n, k, t;
    while (true) {
        scanf("%d %d", &n ,&k);
        if (n == 0)
            break;

        for (int i = 0; i <= n; i++) {
            v[i].index = i;
            v[i].sumto = 0;
        }

        for (int i = 1; i <= n; i++) {
            scanf("%d", &v[i].sumto);
            v[i].sumto = v[i-1].sumto + v[i].sumto;
        }

        std::sort(v, v + n + 1);

        for (int i = 0; i < k; i++) {
            scanf("%d", &t);
            boundFind(n, t);
        }
    }
    return 0;
}