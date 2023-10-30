#include <bits/stdc++.h>

struct Node {
    struct Node* next;
    struct Node* prev;
    int val;
    Node() : val(0), next(nullptr), prev(nullptr) {}
    explicit Node(int val) : val(val), next(nullptr), prev(nullptr) {}
};

struct {
    Node head;
    int size;
} list;

static inline void 
MakeList(int n)
{
    list.head.next = &list.head;
    list.head.prev = &list.head;
    list.size = 0;
    for (int i = 0; i < n; i++) {
        Node* p = new Node(n - i);
        p->next = list.head.next;
        p->prev = &list.head;
        list.head.next->prev = p;
        list.head.next = p;
        list.size++;
    }
}

static inline bool 
IsEmpty() { return list.size == 0; }

static inline void 
Evict(Node** pp)
{
    Node *p = *pp;

    list.size--;
    printf((IsEmpty() ? "%d\n" : "%d "), p->val);

    p->next->prev = p->prev;
    p->prev->next = p->next;
    *pp = p->next;
    delete p;
}

static inline void MainLoop(int m) {
    int c = 1;
    Node *p = list.head.next;
    while (p != nullptr) {

        if (p == &list.head) {
            p = (IsEmpty()? nullptr: p->next);
            continue;
        }

        if (c != m) {
            p = p->next;
        } else {
            Evict(&p);
        }
        
        c = c % m + 1;
    }
}

int 
main()
{
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        exit(-1);
    }
    MakeList(n);
    MainLoop(m);
    exit(0);
}