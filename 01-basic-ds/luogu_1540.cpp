#include <bits/stdc++.h>

constexpr auto MAX = 1024;
constexpr auto HSIZE = 1003;

int hash[HSIZE] = {0};

struct {
    int size;
    int head, tail;
    int val[MAX];
} queue;

// MAX should be more than size,
// so that isFull() and isEmpty() are distinguishable.

static inline bool isFull() {
    return (queue.head + queue.size) % MAX == queue.tail;
}

static inline bool isEmpty() {
    return queue.head == queue.tail;
}

static inline int find(int target) {
    for (int i = queue.head; i != queue.tail; i = (i + 1) % MAX)
        if (queue.val[i] == target)
            return i;
    return -1;
}


int
main()
{
    int m, n, x;
    int i, idx;
    int cnt = 0;
    if (scanf("%d %d", &m, &n) != 2) {
        exit(-1);
    }

    queue.size = m;
    queue.head = queue.tail = 0;

    for (i = 0; i < n; i++) {
        if (scanf("%d", &x) != 1) {
            exit(-1);
        }
        
        if (hash[x % HSIZE])
            continue;

        cnt++;

        hash[x % HSIZE] = 1; 

        if (isFull()) {
            hash[queue.val[queue.head] % HSIZE] = 0;
            queue.head = (queue.head + 1) % MAX;
            queue.val[queue.tail] = x;
            queue.tail = (queue.tail + 1) % MAX;
        } else {
            queue.val[queue.tail] = x;
            queue.tail = (queue.tail + 1) % MAX;
        }
    }
    
    printf("%d\n", cnt);
    exit(0);
}