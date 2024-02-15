#include <bits/stdc++.h>

#define LEFT(x) ((x) << 1)
#define RIGHT(x) (LEFT(x) + 1)
#define PARENT(x) ((x) >> 1)
#define SIZE 1000001
int a[SIZE];
int len = 0;

int
top()
{
    if (len == 0) {
        fprintf(stderr, "heap is empty!\n");
        exit(1);
    }
    return a[1];
}

void
pop()
{
    int i, son;

    if (len == 0) {
        fprintf(stderr, "heap is empty!\n");
        exit(1);
    }

    a[1] = a[len--];
    if (len != 0) {
        i = 1;
        while (LEFT(i) <= len) { // 至少有一个孩子
            son = LEFT(i);
            if (RIGHT(i) <= len && a[LEFT(i)] > a[RIGHT(i)]) // 有两个孩子, 并且右孩子小
                son = RIGHT(i);
            
            if (a[i] > a[son]) {
                std::swap(a[i], a[son]);
                i = son;
            } else break;
        }
    }
}


/// 上浮, 插入新元素
void
push(int x)
{
    a[++len] = x;
    int i = len;
    while (i > 1 && a[i] < a[PARENT(i)]) {
        std::swap(a[i], a[PARENT(i)]);
        i = PARENT(i);
    }
}

int
main()
{
    int n, op, x;

    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> op;

        switch (op)
        {
        case 1:
            std::cin >> x;
            push(x);
            break;

        case 2:
            std::cout << top() << std::endl;
            break;

        case 3:
            pop();
        
        default:
            break;
        }
    }

}