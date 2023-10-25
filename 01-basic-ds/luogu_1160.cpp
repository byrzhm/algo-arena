#include <bits/stdc++.h>

const int N = 100005;

struct {
    int previd, nextid;
} nodes[N] = {0};

int
main()
{
    int m, n;
    int k, p, x;
    int i;
    int previd, nextid;

    if (scanf("%d", &n) != 1) {
        exit(-1);
    }

    nodes[0].nextid = 1;
    nodes[0].previd = 1;

    nodes[1].nextid = 0;
    nodes[1].previd = 0;

    for (i = 1; i < n; i++) {
        if (scanf("%d %d", &k, &p) != 2) {
            exit(-1);
        }
        
        if (p == 0) { // left
            nodes[i+1].nextid = k;
            nodes[i+1].previd = nodes[k].previd;
            previd = nodes[k].previd;
            nodes[previd].nextid = i+1;
            nodes[k].previd = i+1;
        } else { // right
            nodes[i+1].nextid = nodes[k].nextid;
            nodes[i+1].previd = k;
            nextid = nodes[k].nextid;
            nodes[nextid].previd = i+1;
            nodes[k].nextid = i+1;
        }
    }

    if (scanf("%d", &m) != 1) {
        exit(-1);
    }

    for (i = 0; i < m; i++) {
        if (scanf("%d", &x) != 1) {
            exit(-1);
        }
        previd = nodes[x].previd;
        nextid = nodes[x].nextid;

        if (nextid != -1) {
            nodes[previd].nextid = nextid;
            nodes[nextid].previd = previd;
            nodes[x].nextid = -1;
            nodes[x].previd = -1;
        }
    }   

    for (i = nodes[0].nextid; i != 0; i = nodes[i].nextid) {
        printf((nodes[i].nextid == 0 ? "%d\n" : "%d "), i);
    }
}